function case1() {
console.log('begin');
async function async1() {
    console.log('async11 start');
    await async2();
    console.log(`async11 end`);
}

async function async2() {
    console.log('async2 working...');
}


async1();
setTimeout(()=> {
    console.log('case1 timeout');
},100);
console.log('end');


//after executed
//begin
//async11 start
//async2 start
//end
//async11 end
}


function case2() {
console.log('begin');
async function async1() {
    console.log('async12 start');
    await async2();
    console.log(`async12 end`);
}

function async2() {
    console.log('async2 working...');
    return Promise.resolve(10);
}


async1();
setTimeout(()=> {
    console.log('case2 timeout');
},100);
console.log('end');


//after executed
//begin
//async12 start
//async2 start
//end
//async12 end
}

function case3() {
console.log('begin');
async function async1() {
    console.log('async13 start');
    await async2().then((r)=> {
        console.log(`r = ${r}`);
        return Promise.resolve(20);
    })
    .then((r)=> {
        console.log(`rr=${r}`);
    });
    console.log(`async13 end`);
}

function async2() {
    console.log('async2 working...');
    return Promise.resolve(10);
}


async1();
setTimeout(()=> {
    console.log('case3 timeout');
},100);
console.log('end');
console.log('end3');
console.log('end3');
console.log('end3');
var ri=0;
for(let i=0; i<100000000; ++i)
    ri+=Math.sin(i);
console.log(`ri=${ri}`);


//after executed
//begin
//async13 start
//async2 start
//end  //warning, end ,then 10;
//r=10
//async13 end
}

var functions = [case1, case2, case3];
for(let i of functions) {
    console.log(`=======${i.name}=========`);
    i();
}

