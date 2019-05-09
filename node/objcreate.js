var obj = {

    a:function(){
        console.log(100)
    },
    b:function(){
        console.log(200)
    },
    c:function(){
        console.log(300)
    },
    t1:'abkjx',
}

var newObj = {};

newObj = Object.create(obj,{
    t1:{
        value:'yupeng', //fixed value
        writable:true,
        configurable: true,
    },
    bar: {
        configurable: false,
        get: function() { return bar; },
        set: function(value) { bar=value }
    },
    k: {
        value:99999,
        writable: true,
        enumerable: true,
        configurable: true,
    },
    /*
    m: {
        //writable: true,
        //enumrable: true,
        //configurable: true,
    },
    */
});

/*
console.log("newObj.k="+newObj.k);
newObj.k = -9999
console.log("newObj.k="+newObj.k);

console.log(newObj.a());
*/

console.log(newObj.t1);
console.log("delete newObj.t1="+delete newObj.t1);
console.log(newObj.t1);

/*
newObj.t1='yupeng1'
console.log(newObj.t1);
newObj.bar=201;
console.log(newObj.bar)
console.log("delete newObj.bar=" +delete newObj.bar);
*/



