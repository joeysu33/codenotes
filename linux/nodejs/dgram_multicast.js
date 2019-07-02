const dgram = require('dgram');
const proc = require('process');
const port = 8000;
const multicast_addr = '230.1.2.3'
//const multicast_addr = '10.88.47.255'

const ser = dgram.createSocket('udp4', (msg, rinfo)=> {
    console.log('Server got message:' + msg + ' from '+
    rinfo.address + ':'+ rinfo.port);
});
ser.on('listening', ()=> {
    const addr = ser.address();
    console.log('Server listening:'+addr.address+':'+addr.port);

    (()=> {
        console.log('Client start to working...');
        var cli = dgram.createSocket('udp4');
        const stdin = proc.stdin;
        if(stdin.isPaused()) stdin.resume();
        stdin.on('data', (data)=> {
            cli.send(data,0,data.length,
               5000, multicast_addr,(err,bytes)=> {
                   if(err) {
                       cli.close();
                       ser.close();
                       console.error('Error occur:' + err.message);
                       proc.exit(1);
                   }
               });
        });
        stdin.on('end',()=> {cli.close();});
    })();
});

//错误写法
//ser.bind(8000, ser.addMembership(multicast_addr);
//正确写法
ser.bind(port, ()=> { ser.addMembership(multicast_addr); });

