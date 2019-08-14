//Promise.all返回一个promise实例，如果所有的
//promise都完成(resolved)，则回调完成，否则如果有一个失败则失败
//失败的原因是第一个失败的promise的结果

const util = require('util');

//都成功
//Promise.resolve返回一个new Promise的resolve
//Promise.reject 返回一个new Promise的reject
Promise.all([Promise.resolve(1), 400, 'AABB',[1,2,3,'s0'],
    new Promise((resolve,reject)=> {
        setTimeout(resolve, Math.random()*4000+1000, 'last-1');
    }),
    new Promise((resolve, reject)=> {
        setTimeout(resolve, Math.random()*2000+1000, 'last');
    })
])
.then((r)=> {
    console.log(`results = ${util.inspect(r)}`);})
.catch((err)=> {
    console.error(util.inspect(err));
});

Promise.all([
Promise.resolve(1),
[6],
Promise.resolve(100),
new Promise((rs, rj)=> {
    setTimeout(()=> {
        rj(1000);
    }, 3000);
}),
new Promise((rs, rj)=> {
    setTimeout(()=> {
        rj(2000);
    }, 2000);
})
])
.then((r)=> {
    console.log(`results = ${util.inspect(r)}`);}
)
.catch((err)=> {
    console.error(`errors = ${util.inspect(err)}`);
});



