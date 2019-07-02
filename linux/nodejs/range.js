function* range(min,max) {
    let i=min, j=max;
    if(i > j ) {
        throw "error min > max";
        return;
    }
    for(let k=Math.round(i); k <= j; ++k) {
        yield k;
    }
}

var r = range(1,5);
console.log(r.next());
console.log(r.next());
console.log(r.next());
console.log(r.next());

//iterator不支持for..in的写法
//for(let n in range(3,8))
//    console.log(n);

