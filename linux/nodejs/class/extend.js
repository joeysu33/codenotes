class Rectangle {
    constructor(name,w, h) {
        this._name = name || "Rectangle";
        this._w = w || 0;
        this._h = h || 0;
    }

    //getter method
    get name() {
        return this._name;
    }

    //setter method
    set name(name) {
        this._name = name;
        return this;
    }

    area() {
        return this._w * this._h;
    }

    say() {
        return `Rectangle says: I am a ${this.name}`;
        //error usage name() can't recognise
        //return `Rectangle says: I am a ${name()}`;
    }
};

class Square extends Rectangle {
    constructor(name, w) {
        super(name, w, w);
    }

    say() {
        return `Square says: I am a ${this.name}`;
    }
};


var r1 = new Rectangle('Joe',20, 10);
var s1 = new Square('foo',30);
console.log(r1.say() + ` area = ${r1.area()}`);
console.log(s1.say() + ` area = ${s1.area()}`);




