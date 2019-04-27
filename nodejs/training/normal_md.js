function ff() {
    if(this === undefined) {
        console.log("strict mode");
    } else {
        console.log("normal mode");
    }
}

ff();
