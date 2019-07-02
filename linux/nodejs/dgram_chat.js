'use strict'

const dgram = require('dgram');
const proc = require('process');

var sport=4000,dport=8000;
if(proc.argv.length < 3) {
    console.log('So less argements node XX.js source_port dest_port');
    process.exit(1);
}

var sport=parseInt(proc.argv[2]);
var dport=parseInt(proc.argv[3]);
try {
    if(sport < 1024) {
        console.log('Error source port number:'+sport);
        proc.exit(2);
    }
    if(dport < 1024) {
        console.log('Error destination port number:'+dport);
        proc.exit(2);
    }
    if(sport === dport) {
        console.log('Error source port === destinationp port');
        proc.exit(100);
    }
} catch(err) {
    console.log('parse error:' + err.message);
    proc.exit(1);
}

if(proc.stdin.isPaused())
    proc.stdin.resume();

var cli = dgram.createSocket('udp4');
proc.stdin.on('data', (data)=> {
    cli.send(data, 0, data.length, dport,(err, bytes)=> {
        if(err) {
            console.error('Error:'+err.message);
            proc.exit(1);
        }
        console.log('=>' + bytes +'bytes are send successfully!');
    });
});

var ser = dgram.createSocket('udp4', (msg, rinfo)=> {
    console.log('Got message:' + msg +
    'from ' + rinfo.address+':'+rinfo.port);
});
ser.on('listening',()=> {
    let addr = ser.address();
    console.log('Server listeing:'+ addr.address+':'+addr.port);
});
ser.bind(sport);



