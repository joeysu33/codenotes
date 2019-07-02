/*!
 * node对yield的支持，是需要function*
 * 如果函数不是function*的，不支持yield操作
 * f.return()可以停止迭代器
 *
 */
function* fib() {
    let x=0,y=1;
    while(true) {
        try {
            yield y;
            console.log("r="+r);
            [x,y] = [y,x+y];
        } catch(e) {
            if(e === "reset") {
                x=0;y=1;
            }
        }
    }
}

f = fib();
for(let i=0; i<10; ++i) console.log(f.next());

//可以通过throw（迭代器的函数）来和yield交互
f.throw("reset");
for(let i=0; i<10;++i) console.log(f.next());
