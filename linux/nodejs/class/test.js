// class and extends demonstration
class Animal {
    constructor(name, gender) {
        this._name = name;
        this._gender = gender;
    }

    getName() { return this._name; }
    setName(name) { this._name = name; return this;}

    eat() { this.action('eat');}
    sleep() {this.action('sleep');}
    action(act) {
        console.log('Animal '+this._name+ ' are doing ' +act +' !');
    }
};

class Dog extends Animal{
    constructor(gender) {
        //super as keywords ,as reference for Animal
        super('Dog', gender);
    }
};

class Cat extends Animal {
    constructor(gender) {
        //super as keywords, as reference for Animal
        super('Cat',gender);
    }
};


const M = 'Male';
const F = 'Female';
var a = new Animal('Tiger', M);
var d = new Dog(M);
var c = new Cat(F);

a.eat();
d.sleep();
c.eat();

