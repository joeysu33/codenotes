function log(m) {
    var d = new Date();
    console.log(`=>${d.valueOf()} ${d} ${m}`);
}
async function async1() {
    log( 'async1 start' )
    await async2()
    log( 'async1 end' )
}

async function async2() {
    log( 'async2' )
}

log( 'script start' )

setTimeout( function () {
    log( 'setTimeout' )
}, 0 )

async1();

new Promise( function ( resolve ) {
    log( 'promise1' )
    resolve();
} ).then( function () {
    log( 'promise2' ) //why promise2 execute before async1 end????
    for(let i=0; i<1000000000; ++i)
        Math.sin(i);
    return Promise.resolve(100);
} ).then(function(v) {
    log(`promise3 ${v}`);
})

log( 'script end' )
