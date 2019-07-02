const util = require('util');
require('http').createServer((req, res) => {
    console.log(`req.url = ${req.url}`);
    let printBack = () => {
        res.writeHead(200, {'content-type': 'text/plain'});
        res.end(util.inspect(req.headers));
    }
    switch(req.url) {
        case '/': {
            res.writeHead(200, {'content-type': 'text/plain'});
            res.end(util.inspect(req.headers));
            break;
        }
        case '/err': {
            res.writeHead(300, {'content-type': 'text/plain'});
            res.end('some errors!');
            break;
        }
        case '/trailer': {
            res.writeHead(200, {'Content-Type': 'text/plain',
                                'Trailer':'Content-MD5'});
            res.write("XXFJDLSFJLJJL");
            res.write("Hello NodeJS!");
            res.write("AAAABBB");
            res.write("SJFDJLSF");
            res.addTrailers({'Content-MD5':'7895bf4b8828b55ceaf47747b4bca667',
            'XXX-FDJLFJ':'ioeiowifwf',
            'ioeiowfi':['ioew','ifeoiwf','fdsf']});
            res.end();
            break;
        }
    default:
        printBack(); break;
    }
}).listen(8000);
