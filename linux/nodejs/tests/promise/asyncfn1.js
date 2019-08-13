//async function用来定义个返回
//AsyncFunction对象的异步函数

function resolveAfter2Sec() {
    return new Promise((resolve,reject) => {
        setTimeout(()=> {
            resolve('resolved');
        }, 2000)
    });
}

async function asyncCall() {
    console.log('calling');
    //等待resolveAfter2Sec执行完成之后再执行console.log('XXX...');
    var result = await resolveAfter2Sec();
    console.log('after calling resolveAfter2Sce');
    console.log(result);
}

asyncCall();

