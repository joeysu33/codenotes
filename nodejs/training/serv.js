var http = require('http');
http.createServer((req, res) => {
    res.writeHead(200, {'Content-Type':'text/plain'});
    res.end('Hello nodejs.\n');
}).listen(8888);

console.log('Server running at http://127.0.0.1:8888');
