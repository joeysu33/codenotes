var o = {
    m: function() {
        var self = this;
        console.log(this == o); //"true" this == o, m是成员方法
        f();

        function f() {
            console.log(this == o); //"false" this是全局或undefined
            console.log(self == o); //"true" self == o
        }
    }
}

o.m();
