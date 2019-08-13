const fs = require('fs');

async function readFileSync(file) {
    var r = await new Promise((resolve,reject)=> {
        if(fs.accessSync(file, fs.constants.F_OK | fs.constants.R_OK))
            reject(`Access rights error`);
        fs.readFile(file, (err,data)=> {
            if(err) {
                reject(err);
                return;
            }
            console.log(`data = ${data}`);
            resolve(data);
        });
    });
    console.log(`results = ${r}`);
}


readFileSync('promise1.js')
.then(readFileSync('asyncfs1.js'))
.catch((err)=> {console.error(err); })
.finally( async ()=> {
    await new Promise((resolve,reject)=> {
        console.log('finally ok');
        resolve('ok');
    });
});

