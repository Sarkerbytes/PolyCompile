/* â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
   POLYCOMPILE FRONTEND â€” script.js
   All interactivity, animations & data
   â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â• */

'use strict';

/* â•â•â•â•â•â•â•â•â•â•â•â• SAMPLE DATA â•â•â•â•â•â•â•â•â•â•â•â• */
const SAMPLE_CODE = {
  java: `//PolyCompile - Your online Compiler.

import java.util.Scanner;

public class Hello {
  public static void main(String[] args) {
    System.out.println("Hello, World!");
  }
}`,
  cpp: `//PolyCompile - Your online Compiler.
  
#include <iostream>
using namespace std;

int main() {
  cout << "Hello, World!" << endl;
  return 0;
}`,
  c: `//PolyCompile - Your online Compiler.
  
#include <stdio.h>

int main() {
  printf("Hello, World!\\n");
  return 0;
}`
};

const FILE_NAMES = {
  java: 'Hello.java',
  cpp: 'hello.cpp',
  c: 'hello.c'
};

const LANG_LABELS = {
  java: 'Java',
  cpp: 'C++',
  c: 'C'
};

/* ------------ OUTPUT DATA ------------ 
   All output comes from the real polycompile.exe via the Node.js server.
   Run `node server.js` in the frontend/ directory, then open http://localhost:3000
 --------------------------------------------------  */

/* --- Placeholder shown before first compilation --- */
const READY_MSG = (tab) => [
  '  PolyCompile - Ready',
  '  ' + '-'.repeat(40),
  '',
  `  No ${tab} output yet.`,
  '',
  '  Write your code in the editor above,',
  '  then click  > Compile & Run  to compile',
  '  with your real PolyCompile compiler.',
].join('\n');

const SERVER_OFFLINE_MSG = [
  '  |         PolyCompile Server Offline           |',
  '  +----------------------------------------------+',
  '',
  '  The backend server is not running.',
  '  Start it with:',
  '',
  '    cd frontend',
  '    node server.js',
  '',
  '  Then open:  http://localhost:3000',
].join('\n');

/* ── Get output for a tab from the real server result ── */
function getOutputData(tab, lang) {
  const real = window._realOutput;
  if (!real) return READY_MSG(tab);
  if (real._offline) return SERVER_OFFLINE_MSG;
  switch (tab) {
    case 'lexical':
      let lexOut = '';
      lexOut += (real.symbols || '(symbol_table.txt was not generated)') + '\n\n';
      lexOut += (real.tokens || '(tokens.txt was not generated)');
      return lexOut;
    case 'ast':       return real.ast       || '(ast.txt was not generated)';
    case 'parsetree': return real.parseTree || '(parse_tree.txt was not generated)';
    case 'semantic':  return real.report    || '(semantic_report.txt was not generated)';
    case 'tac':       return real.tac       || '(tac.txt was not generated)';
    case 'opt':       return real.opt       || '(optimized_tac.txt was not generated)';
    case 'asm':       return real.asm       || '(target_code.asm was not generated)';
    case 'exec':      return real.exec      || '(no execution output)';
    default:          return '';
  }
}

const OUTPUT_FILES = {
  lexical:   'output/tokens.txt & symbol_table.txt',
  ast:       'output/ast.txt',
  parsetree: 'output/parse_tree.txt',
  semantic:  'output/semantic_report.txt',
  tac:       'output/tac.txt',
  opt:       'output/optimized_tac.txt',
  asm:       'output/target_code.asm'
};

/* --- Global WebSocket & Terminal State --- */
let ws = null;
let currentLang = 'java';
let currentOutputTab = 'lexical';
let pipelineTimer = null;
let pipelinePhase = 0;
let isAnimating = false;
let countersStarted = false;

(function initParticles() {
  const canvas = document.getElementById('particleCanvas');
  if (!canvas) return;
  const ctx = canvas.getContext('2d');

  let W, H, particles = [], animFrame;

  const PARTICLE_COUNT = 80;
  const COLORS = ['rgba(0,212,255,', 'rgba(124,58,237,', 'rgba(255,0,128,', 'rgba(0,255,136,'];

  function resize() {
    W = canvas.width = window.innerWidth;
    H = canvas.height = window.innerHeight;
  }

  function createParticle() {
    const color = COLORS[Math.floor(Math.random() * COLORS.length)];
    return {
      x: Math.random() * W,
      y: Math.random() * H,
      r: Math.random() * 1.5 + 0.3,
      vx: (Math.random() - 0.5) * 0.4,
      vy: (Math.random() - 0.5) * 0.4,
      alpha: Math.random() * 0.5 + 0.1,
      color
    };
  }

  function initParticles() {
    particles = [];
    for (let i = 0; i < PARTICLE_COUNT; i++) particles.push(createParticle());
  }

  function drawConnections() {
    for (let i = 0; i < particles.length; i++) {
      for (let j = i + 1; j < particles.length; j++) {
        const dx = particles[i].x - particles[j].x;
        const dy = particles[i].y - particles[j].y;
        const dist = Math.sqrt(dx * dx + dy * dy);
        if (dist < 120) {
          const alpha = (1 - dist / 120) * 0.12;
          ctx.beginPath();
          ctx.moveTo(particles[i].x, particles[i].y);
          ctx.lineTo(particles[j].x, particles[j].y);
          ctx.strokeStyle = `rgba(0,212,255,${alpha})`;
          ctx.lineWidth = 0.5;
          ctx.stroke();
        }
      }
    }
  }

  function tick() {
    ctx.clearRect(0, 0, W, H);
    drawConnections();
    for (const p of particles) {
      p.x += p.vx;
      p.y += p.vy;
      if (p.x < 0 || p.x > W) p.vx *= -1;
      if (p.y < 0 || p.y > H) p.vy *= -1;
      ctx.beginPath();
      ctx.arc(p.x, p.y, p.r, 0, Math.PI * 2);
      ctx.fillStyle = p.color + p.alpha + ')';
      ctx.fill();
    }
    animFrame = requestAnimationFrame(tick);
  }

  resize();
  initParticles();
  tick();

  window.addEventListener('resize', () => { resize(); initParticles(); });

  // Pause when hero not visible
  const heroObs = new IntersectionObserver(entries => {
    if (!entries[0].isIntersecting) {
      cancelAnimationFrame(animFrame);
    } else {
      tick();
    }
  }, { threshold: 0 });
  const hero = document.getElementById('hero');
  if (hero) heroObs.observe(hero);
})();

/* â•â•â•â•â•â•â•â•â•â•â•â• TYPEWRITER â•â•â•â•â•â•â•â•â•â•â•â• */
(function initTypewriter() {
  const el = document.getElementById('typewriter');
  if (!el) return;
  const words = ['C Programs', 'C++ Applications', 'Java Classes', 'Multi-Language Code'];
  let wordIdx = 0, charIdx = 0, deleting = false;

  function tick() {
    const word = words[wordIdx];
    if (deleting) {
      el.textContent = word.slice(0, charIdx--);
      if (charIdx < 0) {
        deleting = false;
        wordIdx = (wordIdx + 1) % words.length;
        setTimeout(tick, 400);
        return;
      }
      setTimeout(tick, 50);
    } else {
      el.textContent = word.slice(0, charIdx++);
      if (charIdx > word.length) {
        deleting = true;
        setTimeout(tick, 2000);
        return;
      }
      setTimeout(tick, 80);
    }
  }
  setTimeout(tick, 800);
})();

/* â•â•â•â•â•â•â•â•â•â•â•â• STAT COUNTERS â•â•â•â•â•â•â•â•â•â•â•â• */
function animateCounters() {
  if (countersStarted) return;
  countersStarted = true;
  const els = document.querySelectorAll('.stat-num[data-target]');
  els.forEach(el => {
    const target = parseInt(el.dataset.target, 10);
    const duration = 1200;
    const start = performance.now();
    function update(now) {
      const t = Math.min((now - start) / duration, 1);
      const eased = 1 - Math.pow(1 - t, 3);
      el.textContent = Math.floor(eased * target);
      if (t < 1) requestAnimationFrame(update);
      else el.textContent = target;
    }
    requestAnimationFrame(update);
  });
}

/* â•â•â•â•â•â•â•â•â•â•â•â• NAVBAR SCROLL â•â•â•â•â•â•â•â•â•â•â•â• */
(function initNavbar() {
  const nav = document.getElementById('navbar');
  if (!nav) return;
  window.addEventListener('scroll', () => {
    nav.classList.toggle('scrolled', window.scrollY > 40);
  }, { passive: true });
})();

/* â•â•â•â•â•â•â•â•â•â•â•â• INTERSECTION OBSERVER (reveal + counters) â•â•â•â•â•â•â•â•â•â•â•â• */
(function initReveal() {
  // Counters trigger when hero stats visible
  const statsObs = new IntersectionObserver(entries => {
    if (entries[0].isIntersecting) animateCounters();
  }, { threshold: 0.5 });
  const stats = document.getElementById('heroStats');
  if (stats) statsObs.observe(stats);

  // Reveal animation for sections
  const revealObs = new IntersectionObserver(entries => {
    entries.forEach(e => {
      if (e.isIntersecting) {
        e.target.classList.add('visible');
        revealObs.unobserve(e.target);
      }
    });
  }, { threshold: 0.1 });

  const tags = ['ideTag', 'pipelineTag', 'outputTag', 'featuresTag'];
  tags.forEach(id => {
    const el = document.getElementById(id);
    if (el) {
      el.closest('.section-header').classList.add('reveal');
      revealObs.observe(el.closest('.section-header'));
    }
  });

  // Phase cards reveal
  document.querySelectorAll('.phase-card').forEach((card, i) => {
    card.classList.add('reveal');
    card.style.transitionDelay = `${i * 80}ms`;
    revealObs.observe(card);
  });

  // Opt cards reveal
  document.querySelectorAll('.opt-card').forEach((card, i) => {
    card.classList.add('reveal');
    card.style.transitionDelay = `${i * 100}ms`;
    revealObs.observe(card);
  });

  // ASM chips reveal
  document.querySelectorAll('.asm-chip').forEach((chip, i) => {
    chip.classList.add('reveal');
    chip.style.transitionDelay = `${i * 40}ms`;
    revealObs.observe(chip);
  });
})();

/* â•â•â•â•â•â•â•â•â•â•â•â• IDE â€” LANGUAGE TABS â•â•â•â•â•â•â•â•â•â•â•â• */
(function initLangTabs() {
  const tabs = document.querySelectorAll('.lang-tab');
  const editor = document.getElementById('codeEditor');
  const filename = document.getElementById('editorFilename');
  const langBadge = document.getElementById('editorLangBadge');

  function switchLang(lang) {
    currentLang = lang;
    tabs.forEach(t => t.classList.toggle('active', t.dataset.lang === lang));
    if (editor) editor.value = SAMPLE_CODE[lang];
    if (filename) filename.textContent = FILE_NAMES[lang];
    if (langBadge) langBadge.textContent = LANG_LABELS[lang];
    updateLineNumbers();
    updateCommandPreview();
    // Clear real output so panel resets to ready-state when language changes
    window._realOutput = null;
    refreshOutputPanel();
  }

  tabs.forEach(tab => {
    tab.addEventListener('click', () => switchLang(tab.dataset.lang));
  });

  // Init
  if (editor) {
    editor.value = SAMPLE_CODE.java;
    updateLineNumbers();
    editor.addEventListener('input', updateLineNumbers);
    editor.addEventListener('keydown', e => {
      if (e.key === 'Tab') {
        e.preventDefault();
        const s = editor.selectionStart;
        const ee = editor.selectionEnd;
        editor.value = editor.value.substring(0, s) + '  ' + editor.value.substring(ee);
        editor.selectionStart = editor.selectionEnd = s + 2;
        updateLineNumbers();
      }
    });
    editor.addEventListener('scroll', () => {
      const ln = document.getElementById('lineNumbers');
      if (ln) ln.scrollTop = editor.scrollTop;
    });
  }
})();

function updateLineNumbers() {
  const editor = document.getElementById('codeEditor');
  const ln = document.getElementById('lineNumbers');
  if (!editor || !ln) return;
  const lines = editor.value.split('\n').length;
  ln.textContent = Array.from({ length: lines }, (_, i) => i + 1).join('\n');
}

/* â•â•â•â•â•â•â•â•â•â•â•â• FLAG CHECKBOXES → COMMAND PREVIEW â•â•â•â•â•â•â•â•â•â•â•â• */
(function initFlags() {
  const flagIds = ['flag-tokens', 'flag-ast', 'flag-sym', 'flag-tac', 'flag-opt', 'flag-asm', 'flag-debug'];
  flagIds.forEach(id => {
    const el = document.getElementById(id);
    if (el) el.addEventListener('change', updateCommandPreview);
  });
  updateCommandPreview();
})();

function updateCommandPreview() {
  const cmdBody = document.getElementById('cmdBody');
  if (!cmdBody) return;

  const flagMap = {
    'flag-tokens': '--tokens',
    'flag-ast': '--ast',
    'flag-sym': '--symbol-table',
    'flag-tac': '--tac',
    'flag-opt': '--opt',
    'flag-asm': '--asm',
    'flag-debug': '--debug'
  };
  const flags = [];
  for (const [id, flag] of Object.entries(flagMap)) {
    const el = document.getElementById(id);
    if (el && el.checked) flags.push(flag);
  }

  const fname = FILE_NAMES[currentLang] || 'Hello.java';
  const cmd = ['polycompile', ...flags, `examples/${fname}`].join(' ');
  cmdBody.textContent = cmd;

  cmdBody.style.color = 'var(--cyan)';
  setTimeout(() => { cmdBody.style.color = ''; }, 300);
}

/* â•â•â•â•â•â•â•â•â•â•â•â• COMPILE BUTTON â•â•â•â•â•â•â•â•â•â•â•â• */
(function initCompileBtn() {
  const btn = document.getElementById('compileBtn');
  const icon = document.getElementById('compileBtnIcon');
  const label = document.getElementById('compileBtnLabel');
  const status = document.getElementById('compileStatus');
  if (!btn) return;

  btn.addEventListener('click', async () => {
    if (btn.classList.contains('running')) return;

    btn.classList.remove('done');
    btn.classList.add('running');
    if (icon) icon.textContent = '';
    if (label) label.textContent = 'Compiling...';
    if (status) { status.textContent = ''; status.style.color = 'var(--cyan)'; }

    const phases = [
      'Lexical Analysis...',
      'Parsing AST...',
      'Semantic Check...',
      'Generating TAC...',
      'Optimizing...',
      'Generating Assembly...',
    ];

    const editorEl = document.getElementById('codeEditor');
    const code = editorEl ? editorEl.value : SAMPLE_CODE[currentLang];
    const stdinEl = document.getElementById('stdinEditor');
    const stdin = stdinEl ? stdinEl.value : '';

    // Animate phase labels while compilation runs
    let phaseIdx = 0;
    const phaseTimer = setInterval(() => {
      if (status && phaseIdx < phases.length) {
        status.textContent = `[Phase ${phaseIdx + 1}/6] ${phases[phaseIdx]}`;
      }
      phaseIdx++;
    }, 300);

    // ── Call real PolyCompile backend (Analysis only) ──
    try {
      const resp = await fetch('/compile', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ code, lang: currentLang })
      });
      if (resp.ok) {
        window._realOutput = await resp.json();
      } else {
        // Server returned an error response
        window._realOutput = { _offline: true };
      }
    } catch (_) {
      // Server not running
      window._realOutput = { _offline: true };
    }

    // Wait for animation to finish all phases
    await new Promise(r => setTimeout(r, Math.max(0, (phases.length - phaseIdx) * 300 + 400)));
    clearInterval(phaseTimer);
    compileDone();
  });

  function compileDone() {
    btn.classList.remove('running');
    btn.classList.add('done');

    const out = window._realOutput;
    const hasPolyError = out && out.polyError;

    if (icon) icon.textContent = !hasPolyError ? '✓' : '✗';

    if (label) label.textContent = !hasPolyError ? 'Compiled by PolyCompile ✓' : 'Compilation Failed';
    if (status) {
      status.textContent = !hasPolyError
        ? '✓ Real PolyCompile output · All phases complete'
        : '✗ Compilation error — see Lexical/Syntax tabs';
      status.style.color = !hasPolyError ? 'var(--green)' : 'var(--pink)';
    }

    switchOutputTab('exec');
    setTimeout(() => {
      document.getElementById('output')?.scrollIntoView({ behavior: 'smooth', block: 'start' });
    }, 400);
    setTimeout(() => {
      btn.classList.remove('done');
      if (icon) icon.textContent = '▶';
      if (label) label.textContent = 'Compile & Run';
      if (status) status.textContent = '';
    }, 4000);
    
    // Start Interactive Execution
    startTerminalSession();
  }
})();

/* ── WebSocket Terminal Logic ── */
function startTerminalSession() {
  const termOut = document.getElementById('terminalOutput');
  const termRow = document.getElementById('termInputRow');
  const termIn  = document.getElementById('terminalInput');
  const termDot = document.getElementById('termStatusDot');
  const termTxt = document.getElementById('termStatusText');
  const termKill = document.getElementById('termKillBtn');
  
  if (!termOut) return;
  termOut.textContent = '';
  termRow.style.display = 'none';
  termKill.style.display = 'none';
  
  if (ws) {
    try { ws.close(); } catch (_) {}
  }
  
  const code = document.getElementById('codeEditor')?.value || SAMPLE_CODE[currentLang];
  
  termDot.className = 'term-status-dot running';
  termTxt.textContent = 'CONNECTING...';
  
  const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
  ws = new WebSocket(`${protocol}//${window.location.host}`);
  
  ws.onopen = () => {
    termDot.className = 'term-status-dot running';
    termTxt.textContent = 'RUNNING';
    termRow.style.display = 'flex';
    termKill.style.display = 'flex';
    termIn.focus();
    
    ws.send(JSON.stringify({ type: 'run', lang: currentLang, code }));
  };
  
  ws.onmessage = (e) => {
    let msg;
    try { msg = JSON.parse(e.data); } catch { return; }
    
    if (msg.type === 'stdout' || msg.type === 'stderr') {
      termOut.textContent += msg.data;
      termOut.parentElement.scrollTop = termOut.parentElement.scrollHeight;
    } else if (msg.type === 'compile_error') {
      termOut.textContent += '\n[Native Compilation Error]\n' + msg.data;
      termOut.parentElement.scrollTop = termOut.parentElement.scrollHeight;
    } else if (msg.type === 'exit') {
      termOut.textContent += `\n\n[Process finished with exit code ${msg.code}]`;
      termOut.parentElement.scrollTop = termOut.parentElement.scrollHeight;
      endSession('finished', 'FINISHED');
    } else if (msg.type === 'error') {
      termOut.textContent += '\n\n[Error] ' + msg.data;
      termOut.parentElement.scrollTop = termOut.parentElement.scrollHeight;
      endSession('error', 'ERROR');
    }
  };
  
  ws.onclose = () => {
    if (termTxt.textContent === 'RUNNING') {
      endSession('finished', 'DISCONNECTED');
    }
  };
  
  ws.onerror = () => {
    endSession('error', 'CONNECTION ERROR');
  };
  
  function endSession(dotClass, txt) {
    termDot.className = 'term-status-dot ' + dotClass;
    termTxt.textContent = txt;
    termRow.style.display = 'none';
    termKill.style.display = 'none';
  }
}

(function initTerminalInput() {
  const termIn = document.getElementById('terminalInput');
  const termSend = document.getElementById('termSendBtn');
  const termKill = document.getElementById('termKillBtn');
  
  function sendInput() {
    if (!ws || ws.readyState !== WebSocket.OPEN) return;
    const val = termIn.value;
    const termOut = document.getElementById('terminalOutput');
    termOut.textContent += val + '\n';
    ws.send(JSON.stringify({ type: 'stdin', data: val }));
    termIn.value = '';
    termOut.parentElement.scrollTop = termOut.parentElement.scrollHeight;
  }
  
  if (termIn) {
    termIn.addEventListener('keydown', (e) => {
      if (e.key === 'Enter') sendInput();
    });
  }
  if (termSend) {
    termSend.addEventListener('click', sendInput);
  }
  if (termKill) {
    termKill.addEventListener('click', () => {
      if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({ type: 'kill' }));
      }
    });
  }
})();

/* â•â•â•â•â•â•â•â•â•â•â•â• PIPELINE ANIMATION â•â•â•â•â•â•â•â•â•â•â•â• */
(function initPipeline() {
  const animBtn = document.getElementById('animatePipelineBtn');
  const resetBtn = document.getElementById('resetPipelineBtn');
  const progress = document.getElementById('pipelineProgress');

  if (animBtn) animBtn.addEventListener('click', startPipelineAnimation);
  if (resetBtn) resetBtn.addEventListener('click', resetPipeline);
})();

function resetPipeline() {
  if (pipelineTimer) clearTimeout(pipelineTimer);
  isAnimating = false;
  pipelinePhase = 0;
  document.querySelectorAll('.phase-card').forEach(c => {
    c.classList.remove('active', 'done');
  });
  const progress = document.getElementById('pipelineProgress');
  if (progress) progress.style.width = '0%';
  const btn = document.getElementById('animatePipelineBtn');
  const icon = document.getElementById('animBtnIcon');
  if (btn) btn.disabled = false;
  if (icon) icon.textContent = '▶';
}

function startPipelineAnimation() {
  if (isAnimating) return;
  resetPipeline();
  isAnimating = true;
  const btn = document.getElementById('animatePipelineBtn');
  const icon = document.getElementById('animBtnIcon');
  if (btn) btn.disabled = true;
  if (icon) icon.textContent = '';

  animateNextPhase();
}

function animateNextPhase() {
  if (pipelinePhase >= 6) {
    isAnimating = false;
    const btn = document.getElementById('animatePipelineBtn');
    const icon = document.getElementById('animBtnIcon');
    if (btn) btn.disabled = false;
    if (icon) icon.textContent = '✓';
    return;
  }

  const cards = document.querySelectorAll('.phase-card');
  const progress = document.getElementById('pipelineProgress');

  // Mark previous as done
  if (pipelinePhase > 0) {
    cards[pipelinePhase - 1]?.classList.replace('active', 'done');
  }

  // Activate current
  cards[pipelinePhase]?.classList.add('active');
  if (progress) progress.style.width = `${((pipelinePhase + 1) / 6) * 100}%`;

  pipelinePhase++;
  pipelineTimer = setTimeout(animateNextPhase, 650);
}

/* â•â•â•â•â•â•â•â•â•â•â•â• OUTPUT TABS â•â•â•â•â•â•â•â•â•â•â•â• */
(function initOutputTabs() {
  const tabs = document.querySelectorAll('.otab');
  tabs.forEach(tab => {
    tab.addEventListener('click', () => switchOutputTab(tab.dataset.tab));
  });
  // Init
  switchOutputTab('lexical');
})();

function switchOutputTab(tab) {
  currentOutputTab = tab;
  const tabs = document.querySelectorAll('.otab');
  tabs.forEach(t => t.classList.toggle('active', t.dataset.tab === tab));

  const analysisPanel = document.getElementById('analysisPanel');
  const terminalPanel = document.getElementById('terminalPanel');
  const content = document.getElementById('outputContent');
  const fileLabel = document.getElementById('opFileLabel');

  if (tab === 'exec') {
    if (analysisPanel) analysisPanel.style.display = 'none';
    if (terminalPanel) terminalPanel.style.display = 'flex';
  } else {
    if (terminalPanel) terminalPanel.style.display = 'none';
    if (analysisPanel) {
      analysisPanel.style.display = 'block';
      content.style.opacity = '0';
      content.style.transform = 'translateY(6px)';
      setTimeout(() => {
        content.textContent = getOutputData(tab, currentLang);
        content.style.opacity = '1';
        content.style.transform = 'translateY(0)';
      }, 150);
    }
    if (fileLabel) fileLabel.textContent = OUTPUT_FILES[tab] || '';
  }
}

/* Silently refresh the current output tab when language changes â€” no tab switch, no fade delay */
function refreshOutputPanel() {
  if (currentOutputTab === 'exec') return; // Don't refresh terminal on language change
  const content = document.getElementById('outputContent');
  const fileLabel = document.getElementById('opFileLabel');
  if (content) {
    content.style.opacity = '0';
    content.style.transform = 'translateY(6px)';
    setTimeout(() => {
      content.textContent = getOutputData(currentOutputTab, currentLang);
      content.style.opacity = '1';
      content.style.transform = 'translateY(0)';
    }, 120);
  }
  if (fileLabel) fileLabel.textContent = OUTPUT_FILES[currentOutputTab] || '';
}

// Copy button
(function initCopyBtn() {
  const btn = document.getElementById('copyOutputBtn');
  const text = document.getElementById('copyBtnText');
  if (!btn) return;

  btn.addEventListener('click', async () => {
    const content = document.getElementById('outputContent');
    if (!content) return;
    try {
      await navigator.clipboard.writeText(content.textContent);
      if (text) text.textContent = 'Copied!';
      btn.style.color = 'var(--green)';
      btn.style.borderColor = 'var(--green)';
      setTimeout(() => {
        if (text) text.textContent = 'Copy';
        btn.style.color = '';
        btn.style.borderColor = '';
      }, 2000);
    } catch {
      if (text) text.textContent = 'Failed';
      setTimeout(() => { if (text) text.textContent = 'Copy'; }, 1500);
    }
  });
})();

// Stdin clear button (Old stdin panel)
(function initStdinClear() {
  const btn = document.getElementById('stdinClearBtn');
  const editor = document.getElementById('stdinEditor');
  if (!btn || !editor) return;
  btn.addEventListener('click', () => {
    editor.value = '';
    editor.focus();
  });
})();

// Terminal copy button
(function initTermCopyBtn() {
  const btn = document.getElementById('copyTermBtn');
  const text = document.getElementById('copyTermText');
  if (!btn) return;
  
  btn.addEventListener('click', async () => {
    const termOut = document.getElementById('terminalOutput');
    if (!termOut) return;
    try {
      await navigator.clipboard.writeText(termOut.textContent);
      if (text) text.textContent = 'Copied!';
      btn.style.color = 'var(--green)';
      btn.style.borderColor = 'var(--green)';
      setTimeout(() => {
        if (text) text.textContent = 'Copy';
        btn.style.color = '';
        btn.style.borderColor = '';
      }, 2000);
    } catch {
      if (text) text.textContent = 'Failed';
      setTimeout(() => { if (text) text.textContent = 'Copy'; }, 1500);
    }
  });
})();

/* Add smooth transition style to output pre */
(function styleOutputPre() {
  const pre = document.getElementById('outputContent');
  if (pre) {
    pre.style.transition = 'opacity 0.15s ease, transform 0.15s ease';
  }
})();

/* â•â•â•â•â•â•â•â•â•â•â•â• ASM CHIP TOOLTIPS â•â•â•â•â•â•â•â•â•â•â•â• */
(function initAsmChips() {
  const tooltip = document.getElementById('asmTooltip');
  const chips = document.querySelectorAll('.asm-chip');
  if (!tooltip) return;

  chips.forEach(chip => {
    chip.addEventListener('mouseenter', e => {
      const desc = chip.dataset.desc;
      if (!desc) return;
      tooltip.textContent = desc;
      tooltip.classList.add('visible');
      positionTooltip(e);
    });

    chip.addEventListener('mousemove', e => positionTooltip(e));

    chip.addEventListener('mouseleave', () => {
      tooltip.classList.remove('visible');
    });

    chip.addEventListener('click', () => {
      chips.forEach(c => c.classList.remove('active'));
      chip.classList.toggle('active');
    });
  });

  function positionTooltip(e) {
    const x = e.clientX + 14;
    const y = e.clientY - 36;
    tooltip.style.left = `${x}px`;
    tooltip.style.top = `${y}px`;
  }
})();

/* â•â•â•â•â•â•â•â•â•â•â•â• SMOOTH SCROLL for nav links â•â•â•â•â•â•â•â•â•â•â•â• */
(function initSmoothNav() {
  document.querySelectorAll('a[href^="#"]').forEach(a => {
    a.addEventListener('click', e => {
      const target = document.querySelector(a.getAttribute('href'));
      if (!target) return;
      e.preventDefault();
      target.scrollIntoView({ behavior: 'smooth', block: 'start' });
    });
  });
})();

/* â•â•â•â•â•â•â•â•â•â•â•â• HERO VISUAL PARALLAX (subtle) â•â•â•â•â•â•â•â•â•â•â•â• */
(function initParallax() {
  const visual = document.getElementById('heroVisual');
  if (!visual) return;
  document.addEventListener('mousemove', e => {
    const cx = window.innerWidth / 2;
    const cy = window.innerHeight / 2;
    const dx = (e.clientX - cx) / cx;
    const dy = (e.clientY - cy) / cy;
    visual.style.transform = `translate(${dx * 8}px, ${dy * 5}px)`;
  }, { passive: true });
})();

/* â•â•â•â•â•â•â•â•â•â•â•â• MATRIX ROW HOVER HIGHLIGHT â•â•â•â•â•â•â•â•â•â•â•â• */
(function initMatrix() {
  const rows = document.querySelectorAll('.matrix-row');
  rows.forEach(row => {
    row.addEventListener('mouseenter', () => {
      row.style.background = 'rgba(0,212,255,0.04)';
    });
    row.addEventListener('mouseleave', () => {
      row.style.background = '';
    });
  });
})();

/* â•â•â•â•â•â•â•â•â•â•â•â• KEYBOARD SHORTCUTS â•â•â•â•â•â•â•â•â•â•â•â• */
document.addEventListener('keydown', e => {
  // Ctrl+Enter → compile
  if ((e.ctrlKey || e.metaKey) && e.key === 'Enter') {
    const btn = document.getElementById('compileBtn');
    if (btn) btn.click();
  }
  // Ctrl+1/2/3 → language tabs
  if (e.ctrlKey && e.key === '1') document.getElementById('tab-java')?.click();
  if (e.ctrlKey && e.key === '2') document.getElementById('tab-cpp')?.click();
  if (e.ctrlKey && e.key === '3') document.getElementById('tab-c')?.click();
});

/* â•â•â•â•â•â•â•â•â•â•â•â• ACTIVE NAV HIGHLIGHT on scroll â•â•â•â•â•â•â•â•â•â•â•â• */
(function initActiveNav() {
  const sections = [
    { id: 'editor', nav: 'navEditor' },
    { id: 'pipeline', nav: 'navPipeline' },
    { id: 'output', nav: 'navOutput' },
    { id: 'features', nav: 'navFeatures' },
  ];

  const obs = new IntersectionObserver(entries => {
    entries.forEach(e => {
      if (e.isIntersecting) {
        const match = sections.find(s => s.id === e.target.id);
        if (match) {
          document.querySelectorAll('.nav-link').forEach(l => l.style.color = '');
          const navEl = document.getElementById(match.nav);
          if (navEl) navEl.style.color = 'var(--cyan)';
        }
      }
    });
  }, { threshold: 0.35 });

  sections.forEach(s => {
    const el = document.getElementById(s.id);
    if (el) obs.observe(el);
  });
})();

/* â•â•â•â•â•â•â•â•â•â•â•â• GLITCH TITLE EFFECT (subtle, on hover) â•â•â•â•â•â•â•â•â•â•â•â• */
(function initGlitch() {
  const title = document.getElementById('heroTitle');
  if (!title) return;

  title.addEventListener('mouseenter', () => {
    title.style.filter = 'drop-shadow(2px 0 var(--pink)) drop-shadow(-2px 0 var(--cyan))';
    setTimeout(() => {
      title.style.filter = 'drop-shadow(0 0 30px rgba(0,212,255,0.4))';
    }, 150);
  });
})();

/* â•â•â•â•â•â•â•â•â•â•â•â• FOOTER TYPING ANIMATION â•â•â•â•â•â•â•â•â•â•â•â• */
(function initFooterAnim() {
  const footer = document.querySelector('.footer');
  if (!footer) return;

  const obs = new IntersectionObserver(entries => {
    if (entries[0].isIntersecting) {
      footer.querySelectorAll('.fchip').forEach((chip, i) => {
        chip.style.opacity = '0';
        chip.style.transform = 'translateY(10px)';
        chip.style.transition = `opacity 0.4s ease ${i * 80}ms, transform 0.4s ease ${i * 80}ms`;
        setTimeout(() => {
          chip.style.opacity = '1';
          chip.style.transform = 'translateY(0)';
        }, 50);
      });
      obs.unobserve(footer);
    }
  }, { threshold: 0.3 });
  obs.observe(footer);
})();

/* â•â•â•â•â•â•â•â•â•â•â•â• PIPELINE AUTO-TRIGGER on scroll â•â•â•â•â•â•â•â•â•â•â•â• */
(function initPipelineAutoTrigger() {
  const pipelineSection = document.getElementById('pipeline');
  if (!pipelineSection) return;

  let triggered = false;
  const obs = new IntersectionObserver(entries => {
    if (entries[0].isIntersecting && !triggered) {
      triggered = true;
      setTimeout(startPipelineAnimation, 600);
    }
  }, { threshold: 0.4 });
  obs.observe(pipelineSection);
})();

/* â•â•â•â•â•â•â•â•â•â•â•â• DONE â•â•â•â•â•â•â•â•â•â•â•â• */
console.log(`
%c  PolyCompile Frontend  
%c  Built with ðŸ’œ â€” Dark Cyberpunk Edition  
%c  Keyboard Shortcuts:
   Ctrl+Enter → Compile & Run
   Ctrl+1     → Switch to Java
   Ctrl+2     → Switch to C++
   Ctrl+3     → Switch to C
`,
  'background:#7c3aed;color:white;padding:4px 12px;border-radius:4px 4px 0 0;font-weight:bold;font-size:14px',
  'background:#0d1526;color:#00d4ff;padding:4px 12px;font-size:12px',
  'background:#0d1526;color:#8892b0;padding:4px 12px;border-radius:0 0 4px 4px;font-size:11px'
);
