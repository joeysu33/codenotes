const dgram = require('dgram');
ser = dgram.createSocket({type:'udp4'}, (message, rinfo)=> {
    console.log("Server got Message:" + message +
    " from " + rinfo.address + ":" + rinfo.port
    );
});

ser.on('listening', ()=> {
    const addr = ser.address();
    console.log("Server listening address:"+addr.address+":"+ addr.port);

    (()=> {
        var cli = dgram.createSocket('udp4');
        var data = Buffer.from('Hello Server!');
        cli.send(data, 0, data.length,
                8000,
                (err, bytes) => {
            if(err) {
                console.log('Client error:'+err.message);
                process.exit(1);
            }
            console.log("Client send :" + bytes + "bytes");
        });
    })();
});

ser.bind(8000);


