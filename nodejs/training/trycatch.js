function f1() {
    var i=0;
    while(i < 10) {
        try {
            console.log("i="+i);
        }finally{
            ++i;
        }
    }
    console.log("=> i="+i);
}

function f2() {
    var i=0;
    while(i < 10) {
        try {
            console.log("i="+i);
            if(i == 5) break;
        }finally{
            ++i;
        }
    }
    console.log("=> i="+i);
}

function f3() {
    var i=0;
    for_loop:
    for(; i<10; ++i) {
        console.log("i="+i);
        if(i==5) break for_loop;
    }
    console.log("=> i="+i);
}

f1();
f2();
f3();


