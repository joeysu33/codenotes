var req = require('http').request('http://localhost:8000/trailer',
    {method:'GET'},
    (res) => {
        /*
        console.log(`StatusCode:${res.statusCode}`);
        console.log(`Headers:${JSON.stringify(res.headers)}`);
        let body='';
        res.on('data', (chunk) => { body+= chunk;});
        res.on('end', ()=> {
            console.log(`BODY=${body}`);
            console.log(`RawTrailer:${res.rawTrailers}`);
            console.log(`Trailers: ${JSON.stringify(res.trailers)}`);
        });
        */

        console.log(`Addresss=${JSON.stringify(res.socket.address())}`);
        console.log(`received: ${res.statusCode}`);
        console.log(`received: ${res.statusMessage}`);
        res.socket.on('data', (data)=> { console.log("chunk="+data);});
        res.socket.on('end', ()=> { console.log("all data received!");});
    });

req.end();
