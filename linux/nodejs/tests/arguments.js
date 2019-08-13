//arguments.callee arguments.caller
//arguments中不再包含caller了，可以从Function中获取

var o1 = {
    f:function() {
        //非strict模式可以访问
        console.log(arguments.callee === o1.f);
        console.log(arguments.caller === o1);
        console.log('callee' in arguments);
        console.log('caller' in arguments);
    }
}

o1.f();
