//set和get是函数，不用":"来分割
function counter(n) {
    return {
        get count (){ return n++; },
        set count (m) {
            if(m <n) throw Error(m+" less than"+n);
            n = m;
        }
    }
}

c1 = counter(1);
c2 = counter(10);

for(var i=0 ; i< 10; ++i) {
    console.log("c1()="+c1.count);
    console.log("c2()="+c2.count);
}

c1.count=1
c2.count=100

