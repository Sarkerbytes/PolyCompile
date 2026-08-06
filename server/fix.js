const fs = require('fs');

const fixes = [
  { bad: /âŸ³/g, good: '' },
  { bad: /â€¦/g, good: '...' },
  { bad: /âœ“/g, good: '✓' },
  { bad: /â–¶/g, good: '▶' },
  { bad: /Â·/g, good: '·' },
  { bad: /â”€/g, good: '─' },
  { bad: /â• /g, good: '═' },
  { bad: /â— /g, good: '●' },
  { bad: /â†’/g, good: '→' }
];

['d:/PolyCompile/PolyCompile/server/script.js', 'd:/PolyCompile/PolyCompile/server/server.js'].forEach(file => {
  if (!fs.existsSync(file)) return;
  let content = fs.readFileSync(file, 'utf8');
  fixes.forEach(f => {
    content = content.replace(f.bad, f.good);
  });
  fs.writeFileSync(file, content, 'utf8');
});
console.log('Fixed characters');
