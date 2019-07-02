/*!
 * node对yield的支持，是需要function*
 * 如果函数不是function*的，不支持yield操作
 *
 */
function* fib() {
    let x=0,y=1;
    while(true) {
        yield y;
        [x,y] = [y,x+y];
    }
}

f = fib();
for(let i=0; i<10; ++i) console.log(f.next());

