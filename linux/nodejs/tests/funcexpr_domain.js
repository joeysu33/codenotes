//函数表达式的作用域，相当于本表达式函数的一个内部变量
//只能在函数内部调用，例如
//

var f = function fact(x) {
    if(x<=1) { return 1; }
    else {
        return x*fact(x-1);
    }
}

console.log("f(10)="+f(5));
fact();
