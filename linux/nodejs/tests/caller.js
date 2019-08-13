//arguments.caller 已经没有，可以使用Function中的
//
function whoCalled() {
    if(whoCalled.caller == null)
        console.log("I was called from the global scope");
    else
        console.log(whoCalled.caller + 'called me!');
}

whoCalled();
(function tf() { whoCalled();})();
