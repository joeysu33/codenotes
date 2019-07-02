const http = require('http') ;
var server = http.createServer();
server.on('request',(req, res) => {
    res.writeHead(200, {"content-type": "text/plain"})

    var left = 10;
    var interval = setInterval(function() {
        if(--left == 0) {
            clearInterval(interval);
            res.end();
            return;
        }
        res.write((new Date()).toString() +"\n");
    }, 500);

});
server.listen(8000);
