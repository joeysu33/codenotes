function* foo() {
    var x = 0x61;
    for(let i=0; i<26;++i)
        yield String.fromCharCode(x++);
}

var str='';
for(let val of foo())
    str += val;
console.log(str);
