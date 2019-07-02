'use strict'

const dgram = require('dgram');
const port=4000;
/*!
 * reuseAddr可以启动多个实例
 */
var ser = dgram.createSocket({type:'udp4', reuseAddr:true},
    (msg, rinfo)=> {
        console.log(`Server got message:${msg} from ${rinfo.address}:${rinfo.port}`);
    });

/*!
 * 由于bind现在从0.10之后修改为异步，所以
 * 设置socket属性的函数均设置在bind的回调中
 * 例如setBroadcast, addMembership
 * 否则会因为没有初始化好socket而导致出错，
 */
ser.on('listening',()=> {
    const stdin = process.stdin;
    stdin.resume();
    setTimeout(()=> {
        var cli = dgram.createSocket('udp4');
        cli.bind({}, ()=> { cli.setBroadcast(true); });
        stdin.on('data',(data)=> {
            cli.send(data,0,data.length,port,'192.168.43.255',(err,bytes)=> {
                if(err) {
                    console.error(`Error message:${err}`);
                    process.exit(1);
                }
                console.log(`${bytes} are sended!`);
            });
        });
    }, 1000);
});
ser.bind(port, ()=> {
    ser.setBroadcast(true);
});


