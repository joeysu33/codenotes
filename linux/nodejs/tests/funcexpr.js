function print(x) { console.log(String(x)); }

function f() { print("I'm outside"); }

(function () {
    //不可以在条件语句中使用function
    //if(false)
    {
        function f() { print("I'm inside"); }
    }
    f();
})();


