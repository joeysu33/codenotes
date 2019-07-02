const util = require('util');
var req = require('http').request({host:'localhost',
                method:'GET', port:8000, path:'/',
                protocol:'http:'},
                (res)=> {
                    console.log(`status code:${res.statusCode}, statusMessage:${res.statusMessage}`);
                    console.log("Received response, and headers:"+
                    `${util.inspect(res.headers)}`);
                });

/*!
 * request can get socket and observe socket*/
req.on('socket', (sock) => {
    console.log("socket allocated by agent!");
    sock.on('connect', ()=> {
        console.log("socket connect to server!");
        console.log(`socket local address+${util.inspect(sock.address())}`);
        console.log(`socket remote address+${util.inspect(sock.remoteAddress)} ,remote port: ${sock.remotePort}`);
        });

    var arr = []
    sock.on('data',(d) => {
        console.log("Received socket data:"+d.toString());
        arr.push(d);
    });
    sock.on('end',()=> {
        console.log("End received data!");
        var body = Buffer.concat(arr);
        console.log(`BODY: ${body.toString('utf8')}`);
    });
});

req.end();
