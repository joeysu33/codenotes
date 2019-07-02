/*
 * zero-length assertion
 * (?=<expr>) 正预测先行断言
 * (?<=<expr>) 正回顾后发断言
 *
 * 否定式
 * (?!<expr>)
 * (?<!<expr>)
 *
 * 正向预测和反向预测的区别：
 * 正向预测和状态机的处理方向相同，
 * 反向预测，首先跳过(?<XXX)的匹配然后再回过头再
 * 判断是否符合断言说明
 *
 * \w 字母（含大小写），数字，下划线
 *
 * zl assertion匹配的是位置和\b之类的类似，都同时
 * 用的时候会有问题
 *
 * 在正则表达式中，如果使用了(),子表达式，可以使用
 * \1,\2...\n来引用子表达式，例如，匹配xml标签
 * (?<=(\<[a-zA-Z]+)\>).+(?=\<\/\1\>);
 * 使用\1来引用前面的子表达式
 */

/*
var s1="ace acee bec def cec ade";
var rx1 = /(?<![ab])e(?=c)/g;
console.log(s1.match(rx1));
console.log(rx1.exec(s1));

var s2="I'm singing whlie you're dancing";
var rx2 = /\b\w+(?=ing\b)/g
s2.match(rx2)
*/

var s3="I'm 1singing whlie you're dancing";
var rx3 = /\b(?<![1-9])[a-zA-Z]+(?=ing\b)/g;
console.log(s3.match(rx3));

var s4="I'm 1singing whlie you're dancing";
//var rx4 = /\b(?<=[1-9])[a-zA-Z]+(?=ing\b)/g; 这种写法有问题
var rx4 = /(?<=\b[1-9])[a-zA-Z]+(?=ing\b)/g;
console.log(s4.match(rx4));
