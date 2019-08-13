var doAdd = (num)=> {
    return new Promise((resolve, reject) => {
        console.log('初始化');
        console.log(`number = ${num}`);
        resolve(num+1);
    });
}

var doErr = ()=> {
    return new Promise((resolve, reject)=> {
        console.log(`make error`);
        reject(`do errors`);
    });
}

async function asyncDoAdd() {
    console.log(`begin add`);
    console.log(`AsyncDoAdd:result = ${await doAdd(1000)}`);
    console.log(`end add`);
}

var splitLine = ()=> { console.log('#'.repeat(20)); }

asyncDoAdd();

splitLine();
//()=> x 等价于 ()=> { return x;}
//(num)=> {return doAdd(num);}
var prom1 = doAdd(10)
.then((num) => doAdd(num))
.then((num) => doAdd(num))
.then((num) => doAdd(num))
.catch((err) => {console.error(err); });


splitLine();
doAdd(20)
.then((num)=> doAdd(num))
.then((num)=> doErr())
.catch((err)=> {console.error(err);});

splitLine();
doAdd(30)
.then((num)=> doAdd(num))
.then((num) => doErr())
.catch((err)=> {console.error(err); })
.finally(()=> {console.log('finally executed.'); });

splitLine();
doAdd(40)
.then((num)=> doAdd(num))
.then((num)=> doErr())
.catch((err)=> {console.error(err); })
.then(()=> {console.log('then after "catch" executed'); });




