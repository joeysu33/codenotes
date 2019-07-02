require('http').createServer((req, res)=> {
    res.setHeader('content-type', 'text/plain');
    res.writeHead(200);

    switch(req.url) {
        case '/':{
            res.write("Hello NodeJS!");
            res.end();
            break;
        }
        case '/test': {
            res.write("Hello Test NodeJS");
            res.end();
            break;
        }
    }
}).listen(8000);
