//闭包

function counter(n) {
    return function() { return n++;}
}

var c1 = counter(10);
for(var i=0; i<10; ++i) console.log(c1());

var c2 = counter(2);
for(var i=0; i<10; ++i) console.log(c2());
