console.log("square(10)="+square(10));   //可以在函数声明之前调用,和变量类似,函数作用域
console.log("square2(10)="+square2(10)); //不可以在表达式之前调用

//函数声明,不可以出现在循环，条件或者try/catch/finally,或with中
function square(x) { return x*x; }

//函数表达式
square2 = function(x) { return x*x;}

console.log("square2(10)="+square2(10));

