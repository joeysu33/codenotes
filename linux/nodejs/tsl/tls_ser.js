'use strict'
const tls =  require('tls');
const fs = require('fs');

var opt = {
    key: fs.readFileSync('./my_key.pem'),
    cert:fs.readFileSync('./my_cert.pem')
};
var ser = tls.createServer(opt);
var clients;
ser.on('secureConnection', (cli)=> {
    var name = cli.address().address+':'+cli.address().port;
    if(!(name in clients)) {
        cli.write('Hello TLS!');
        clients[name]=1;
    }

    cli.on('data', (data)=> {
        var addr =cli.address();
        var text=data.toString();
        if(text.search(/quit/ig)) {
            cli.close();
            console.log('Client quit:'+ name);
            return;
        }
        console.log(name +
        '=> Got some data from the client:' + data);
    });
});
ser.listen(8000, ()=> {
    const addr = ser.address();
    console.log('TLS server listening:'+
        addr.address + ':'+ addr.port);
});

