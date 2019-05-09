function inherit2(p) {
    var ty = typeof p;
    if(ty != "object" && ty != "function") {
        throw TypeError();
    }

    function f() {};
    f.prototype = p;
    return new f();
}

function inherit(p) {
    if(p == null) throw TypeError();

    if(Object.create)
        return Object.create(p);
    return  inherit2(p);
}

function object2String(o) {
    s = "{";
    for(var i in o) {
        s += i +"="+ String(o[i])+" ";
    }
    s += "}";
    return s;
}


var t = {x:1, y:2} ;
var o1 = inherit2(t);
var o2 = Object.create(t);

console.log("o1="+object2String(o1));
console.log("o2="+object2String(o2));
