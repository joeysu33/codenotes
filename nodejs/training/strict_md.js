'use strict'

function ff() {
    if(this === undefined) {
        console.log("strict mode");
    } else {
        console.log("nornal mode");
    }
}

ff();
