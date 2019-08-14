function resolveAfter2Seconds(x) {
  return new Promise(resolve => {
    setTimeout(() => {
      resolve(x);
    }, 2000);
  });
};

//异步函数
// async function expression assigned to a variable
var add1 = async function(x) {
  var a = await resolveAfter2Seconds(20);
  var b = await resolveAfter2Seconds(30);
  return x + a + b;
}

add1(10).then(v => {
  console.log(v);  // 4 秒后打印 60
});

//异步函数表达式
//IIFE Immidiately Invokded Function Expression
(async function(x) { // async function expression used as an IIFE
  var p_a = resolveAfter2Seconds(20);
  var p_b = resolveAfter2Seconds(30);
  return x + await p_a + await p_b;
})(10).then(v => {
  console.log(v);  // 2 秒后打印 60
});
