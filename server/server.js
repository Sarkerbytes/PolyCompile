'use strict';

const express      = require('express');
const path         = require('path');
const fs           = require('fs');
const http         = require('http');
const { WebSocketServer } = require('ws');
const { execFile, spawn } = require('child_process');

const app    = express();
const server = http.createServer(app);
const wss    = new WebSocketServer({ server });
const PORT   = process.env.PORT || 3000;

/* --- Paths --------------------------------------- */
const FRONTEND_DIR = __dirname;
const ROOT_DIR     = path.resolve(FRONTEND_DIR, '..');
const POLY_EXE     = path.join(ROOT_DIR, process.platform === 'win32' ? 'polycompile.exe' : 'polycompile');
const OUTPUT_DIR   = path.join(ROOT_DIR, 'output');
const TEMP_DIR     = path.join(FRONTEND_DIR, 'temp');

/* --- Bootstrap ----------------------------------- */
if (!fs.existsSync(TEMP_DIR)) fs.mkdirSync(TEMP_DIR, { recursive: true });
if (!fs.existsSync(POLY_EXE)) {
  console.error(`\n  [ERROR] polycompile not found at: ${POLY_EXE}`);
  process.exit(1);
}

/* --- Middleware ---------------------------------- */
app.use(express.json({ limit: '2mb' }));
app.use(express.static(FRONTEND_DIR));

/* --- Health check -------------------------------- */
app.get('/ping', (_, res) => res.json({ status: 'ok', compiler: POLY_EXE }));

/* ─────────────────────────────────────────────────────────────────
   POST /compile  — runs polycompile for analysis phases only
   (tokens, AST, symbol table, TAC, opt, asm)
   ─────────────────────────────────────────────────────────────── */
app.post('/compile', (req, res) => {
  const { code = '', lang = 'java' } = req.body;
  if (!code.trim()) return res.status(400).json({ error: 'No code provided.' });

  /* write source file */
  let fileName;
  if (lang === 'java') {
    const m = code.match(/public\s+class\s+(\w+)/);
    fileName = (m ? m[1] : 'Main') + '.java';
  } else if (lang === 'cpp') {
    fileName = 'main.cpp';
  } else {
    fileName = 'main.c';
  }
  const filePath = path.join(TEMP_DIR, fileName);
  try { fs.writeFileSync(filePath, code, 'utf8'); }
  catch (e) { return res.status(500).json({ error: 'Could not write temp file: ' + e.message }); }

  const COMPILE_FLAGS = ['--tokens', '--ast', '--symbol-table', '--tac', '--opt', '--asm', filePath];

  execFile(POLY_EXE, COMPILE_FLAGS, { cwd: ROOT_DIR, timeout: 15000 }, (err, stdout, stderr) => {
    const readOut = (name) => {
      try { return fs.readFileSync(path.join(OUTPUT_DIR, name), 'utf8').trim(); }
      catch { return `(${name} not generated)`; }
    };

    res.json({
      tokens:    readOut('tokens.txt'),
      ast:       readOut('ast.txt'),
      parseTree: readOut('parse_tree.txt'),
      symbols:   readOut('symbol_table.txt'),
      report:    readOut('semantic_report.txt'),
      tac:       readOut('tac.txt'),
      opt:       readOut('optimized_tac.txt'),
      asm:       readOut('target_code.asm'),
      polyError: err ? ([stdout, stderr].filter(Boolean).join('\n').trim() || err.message) : null
    });
  });
});

/* ─────────────────────────────────────────────────────────────────
   WebSocket — interactive terminal session
   Protocol (JSON messages):

   CLIENT → SERVER:
     { type: 'run',   lang, code }   start a native compile + run
     { type: 'stdin', data }         send a line of input to running process
     { type: 'kill'  }               terminate the running process

   SERVER → CLIENT:
     { type: 'stdout', data }        chunk of program output
     { type: 'stderr', data }        chunk of program stderr
     { type: 'compile_error', data } native compiler error
     { type: 'exit',   code }        process finished with exit code
     { type: 'error',  data }        server-side error
   ─────────────────────────────────────────────────────────────── */
wss.on('connection', (ws) => {
  let child = null;
  let exePath = null;
  let lang = null;

  const send = (obj) => {
    if (ws.readyState === ws.OPEN) ws.send(JSON.stringify(obj));
  };

  const cleanup = () => {
    if (child) { try { child.kill(); } catch (_) {} child = null; }
    if (exePath) { try { fs.unlinkSync(exePath); } catch (_) {} exePath = null; }
  };

  ws.on('message', (raw) => {
    let msg;
    try { msg = JSON.parse(raw); } catch { return; }

    /* ── stdin: pipe text into the running process ── */
    if (msg.type === 'stdin') {
      if (child && child.stdin && !child.stdin.destroyed) {
        const line = msg.data.endsWith('\n') ? msg.data : msg.data + '\n';
        child.stdin.write(line);
      }
      return;
    }

    /* ── kill ── */
    if (msg.type === 'kill') { cleanup(); return; }

    /* ── run: compile + execute ── */
    if (msg.type === 'run') {
      if (child) cleanup(); // kill any existing process

      lang = msg.lang || 'c';
      const code = msg.code || '';

      let processedCode = code;
      if (lang === 'c' || lang === 'cpp') {
        processedCode = `#include <stdio.h>\n` + code.replace(/(int|void)\s+main\s*\([^)]*\)\s*\{/, "$&\n  setvbuf(stdout, NULL, _IONBF, 0);\n");
      }

      /* write source */
      let fileName;
      if (lang === 'java') {
        const m = code.match(/public\s+class\s+(\w+)/);
        fileName = (m ? m[1] : 'Main') + '.java';
      } else if (lang === 'cpp') {
        fileName = 'main.cpp';
      } else {
        fileName = 'main.c';
      }
      const srcPath = path.join(TEMP_DIR, fileName);
      try { fs.writeFileSync(srcPath, processedCode, 'utf8'); }
      catch (e) { send({ type: 'error', data: 'Could not write source: ' + e.message }); return; }

      /* compile */
      const base = path.basename(srcPath, path.extname(srcPath));
      const outDir = path.dirname(srcPath);
      exePath = path.join(outDir, base + (process.platform === 'win32' ? '.exe' : ''));

      let compiler, compileArgs;
      if (lang === 'c') {
        compiler = 'gcc'; compileArgs = [srcPath, '-o', exePath, '-lm'];
      } else if (lang === 'cpp') {
        compiler = 'g++'; compileArgs = [srcPath, '-o', exePath, '-std=c++17', '-lm'];
      } else {
        compiler = 'javac'; compileArgs = ['-d', outDir, srcPath];
      }

      execFile(compiler, compileArgs, { timeout: 20000 }, (compErr, _out, compStderr) => {
        if (compErr) {
          send({ type: 'compile_error', data: compStderr || compErr.message });
          exePath = null;
          return;
        }

        /* run */
        let runCmd, runArgs;
        if (lang === 'java') {
          const className = path.basename(srcPath, '.java');
          runCmd = 'java'; runArgs = ['-cp', outDir, className];
          exePath = null; // nothing to delete for java
        } else {
          runCmd = exePath; runArgs = [];
        }

        child = spawn(runCmd, runArgs, { stdio: ['pipe', 'pipe', 'pipe'] });

        const killTimer = setTimeout(() => {
          send({ type: 'stdout', data: '\n[Process timed out after 30 seconds]\n' });
          cleanup();
        }, 30000);

        child.stdout.on('data', (d) => send({ type: 'stdout', data: d.toString() }));
        child.stderr.on('data', (d) => send({ type: 'stderr', data: d.toString() }));

        child.on('close', (code) => {
          clearTimeout(killTimer);
          cleanup();
          send({ type: 'exit', code: code ?? 0 });
        });

        child.on('error', (e) => {
          clearTimeout(killTimer);
          send({ type: 'error', data: e.message });
          cleanup();
        });
      });
    }
  });

  ws.on('close', () => cleanup());
});

/* --- Start --------------------------------------- */
server.listen(PORT, () => {
  console.log(`\n  > Browser  :  http://localhost:${PORT}`);
  console.log(`  > Compiler :  ${POLY_EXE}`);
  console.log(`  > Output   :  ${OUTPUT_DIR}`);
  console.log(`  > Temp dir :  ${TEMP_DIR}`);
  console.log('\n  Ready. Waiting for requests...\n');
});
