function showProperty(o) {
    var level=1;
    while(o) {
        console.log("=> level="+level++);
        for(var i in o) {
            console.log(i+"="+o[i]);
        }
        o = o.__proto__
    }
}

var t = {x:1, y:2}
var a = Object.create(t);

a.z = 1000
a.k = 200
a.x = 999
a.y = -999

console.log("a's prototype="+a.prototype);
console.log("a's __proto__="+a.__proto__);
showProperty(a);

showProperty(new Date());

