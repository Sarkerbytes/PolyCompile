const http = require("http");
const fs = require("fs");
const req = http.request("http://localhost:3000/compile", {
    method: "POST",
    headers: { "Content-Type": "application/json" }
}, (res) => {
    let data = "";
    res.on("data", d => data += d);
    res.on("end", () => console.log(JSON.parse(data).exec));
});
req.write(JSON.stringify({ code: fs.readFileSync("frontend/test_req.js", "utf8"), lang: "cpp" }));
req.end();
