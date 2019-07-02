const util = require('util');
var req= require('http').request({method:'GET',host:'localhost',
            protocol:'http:',port:'8000'}, (res)=> {
                console.log(`Headers: ${util.inspect(res.headers)}`);
                var b=[]
                res.on('data', (d) => {
                    console.log("d is instance of Buffer:" + (d instanceof Buffer));
                    b.push(d);
                    });
                res.on('end', ()=> {
                    let buf = Buffer.concat(b);
                    console.log(buf.toString('utf8'));
                });
            }).end();

