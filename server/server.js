'use strict';

const express      = require('express');
const path         = require('path');
const fs           = require('fs');
const { execFile } = require('child_process');

const app  = express();
const PORT = process.env.PORT || 3000;

/* --- Paths --------------------------------------- */
const FRONTEND_DIR = __dirname;
const ROOT_DIR     = path.resolve(FRONTEND_DIR, '..');
const POLY_EXE     = path.join(ROOT_DIR, process.platform === 'win32' ? 'polycompile.exe' : 'polycompile');
const OUTPUT_DIR   = path.join(ROOT_DIR, 'output');
const TEMP_DIR     = path.join(FRONTEND_DIR, 'temp');

/* --- Bootstrap ----------------------------------- */
if (!fs.existsSync(TEMP_DIR)) fs.mkdirSync(TEMP_DIR, { recursive: true });

if (!fs.existsSync(POLY_EXE)) {
  console.error(`\n  [ERROR] polycompile executable not found at:\n  ${POLY_EXE}`);
  console.error('  Run `make` or `mingw32-make` in the project root to build it first.\n');
  process.exit(1);
}

/* --- Middleware ---------------------------------- */
app.use(express.json({ limit: '2mb' }));
app.use(express.static(FRONTEND_DIR));

/* --- Health check -------------------------------- */
app.get('/ping', (_, res) => res.json({ status: 'ok', compiler: POLY_EXE }));

/* --- POST /compile ------------------------------- */
app.post('/compile', (req, res) => {
  const { code = '', lang = 'java' } = req.body;

  if (!code.trim()) return res.status(400).json({ error: 'No code provided.' });

  /* Determine source file name */
  let fileName;
  if (lang === 'java') {
    const classMatch = code.match(/public\s+class\s+(\w+)/);
    fileName = (classMatch ? classMatch[1] : 'Main') + '.java';
  } else if (lang === 'cpp') {
    fileName = 'main.cpp';
  } else {
    fileName = 'main.c';
  }

  const filePath = path.join(TEMP_DIR, fileName);

  try { fs.writeFileSync(filePath, code, 'utf8'); }
  catch (e) { return res.status(500).json({ error: 'Could not write temp file: ' + e.message }); }

  const COMPILE_FLAGS = [
    '--tokens', '--ast', '--symbol-table',
    '--tac', '--opt', '--asm',
    filePath
  ];

  /* Run 1: compile with all output flags */
  execFile(POLY_EXE, COMPILE_FLAGS, { cwd: ROOT_DIR, timeout: 15000 },
    (err1, stdout1, stderr1) => {

      const compilerOut = [stdout1, stderr1].filter(Boolean).join('\n').trim();
      const ERROR_RE    = /\[error\]|syntax error|parse error|semantic error|undeclared|undefined|unexpected token|error:/i;
      const hasError    = !!err1 || ERROR_RE.test(compilerOut);
      const compileError = hasError ? (compilerOut || err1?.message || 'Compilation failed') : null;

      /* Run 2: execute to capture program stdout */
      execFile(POLY_EXE, [filePath], { cwd: ROOT_DIR, timeout: 15000 },
        (err2, stdout2, stderr2) => {

          const programOutput = compileError
            ? '(program not executed due to compile errors)'
            : ((stdout2 || '').trim() || (err2 ? 'Runtime error: ' + (stderr2 || err2.message) : '(no output)'));

          /* Read all output files */
          const readOut = (name, fallback) => {
            const fp = path.join(OUTPUT_DIR, name);
            try   { return fs.readFileSync(fp, 'utf8').trim(); }
            catch { return fallback || `(${name} not generated)`; }
          };

          const tokens    = readOut('tokens.txt');
          const ast       = readOut('ast.txt');
          const parseTree = readOut('parse_tree.txt');
          const symbols   = readOut('symbol_table.txt');
          const tac       = readOut('tac.txt');
          const opt       = readOut('optimized_tac.txt');
          const asm       = readOut('target_code.asm');

          /* Build execution report */
          const progLines  = programOutput.split('\n').map(l => '  ' + l).join('\n');
          const statusLine = compileError
            ? '  ✗ Compilation FAILED\n  ✗ Fix the errors above and recompile'
            : '  ✓ Compilation Successful\n  ✓ Exit Code: 0\n  ✓ No warnings, no errors';

          const execParts = [];
          if (compileError) {
            execParts.push(
              '  Compiler Errors:',
              compileError.split('\n').map(l => '  ' + l).join('\n'),
              ''
            );
          }
          execParts.push(
            '  Program Output:',
            progLines,
            '',
            '  Compilation Status:',
            statusLine
          );
          const exec = execParts.join('\n');

          res.json({
            tokens, ast, parseTree, symbols, tac, opt, asm, exec,
            success: !compileError,
            error:   compileError
          });
        }
      );
    }
  );
});

/* --- Start --------------------------------------- */
app.listen(PORT, () => {
  console.log(`\n  > Browser  :  http://localhost:${PORT}`);
  console.log(`  > Compiler :  ${POLY_EXE}`);
  console.log(`  > Output   :  ${OUTPUT_DIR}`);
  console.log(`  > Temp dir :  ${TEMP_DIR}`);
  console.log('\n  Ready. Waiting for compile requests...\n');
});
