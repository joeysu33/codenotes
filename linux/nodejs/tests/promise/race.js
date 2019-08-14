//Promise.race(iterator) 返回一个promise,一旦迭代器中的某个
//promise解决或拒绝，则返回的promise就解决或拒绝

const util = require('util');
Promise.race([
new Promise((resolve,reject)=> {
    setTimeout(resolve, 100, 1);
}),
new Promise((resolve,reject)=> {
    setTimeout(resolve, 101, 2);
    }),
new Promise((resolve,reject)=> {
    setTimeout(resolve, 98, 3);
    //setTimeout(resolve, 99, 3);
    }),
new Promise((resolve,reject)=> {
    setTimeout(reject, 101, 4);
    }),
new Promise((resolve, reject)=> {
    setTimeout(reject, 100, 5);
    })
]).then((r)=> {
    console.log(`results: ${util.inspect(r)}`);
}).catch((err)=> {
    console.log(`errors: ${util.inspect(err)}`);
});


Promise.race([
new Promise((resolve,reject)=> {
    setTimeout(resolve, 100, 1);
}),
new Promise((resolve,reject)=> {
    setTimeout(resolve, 101, 2);
    }),
'<<{}>>',
new Promise((resolve,reject)=> {
    setTimeout(resolve, 100, 3);
    }),
new Promise((resolve,reject)=> {
    setTimeout(reject, 101, 4);
    }),
new Promise((resolve, reject)=> {
    setTimeout(reject, 100, 5);
    })
]).then((r)=> {
    console.log(`results: ${util.inspect(r)}`);
}).catch((err)=> {
    console.log(`errors: ${util.inspect(err)}`);
});


Promise.race([
new Promise((resolve,reject)=> {
    setTimeout(resolve, 100, 1);
}),
new Promise((resolve,reject)=> {
    setTimeout(resolve, 101, 2);
    }),
Promise.reject('race3'),
new Promise((resolve,reject)=> {
    setTimeout(resolve, 100, 3);
    }),
new Promise((resolve,reject)=> {
    setTimeout(reject, 101, 4);
    }),
new Promise((resolve, reject)=> {
    setTimeout(reject, 100, 5);
    })
]).then((r)=> {
    console.log(`results: ${util.inspect(r)}`);
}).catch((err)=> {
    console.log(`errors: ${util.inspect(err)}`);
});

Promise.race([
new Promise((resolve,reject)=> {
    setTimeout(resolve, 100, 1);
}),
new Promise((resolve,reject)=> {
    setTimeout(resolve, 101, 2);
    }),
Promise.resolve('race4'),
new Promise((resolve,reject)=> {
    setTimeout(resolve, 100, 3);
    }),
new Promise((resolve,reject)=> {
    setTimeout(reject, 101, 4);
    }),
new Promise((resolve, reject)=> {
    setTimeout(reject, 100, 5);
    })
]).then((r)=> {
    console.log(`results: ${util.inspect(r)}`);
}).catch((err)=> {
    console.log(`errors: ${util.inspect(err)}`);
});
