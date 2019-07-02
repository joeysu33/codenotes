var dgram = require('dgram');

var host = '230.1.2.3'
var port = 4002;

var socket = dgram.createSocket('udp4');

socket.on('listening', function () {
    var address = socket.address();
    console.log('UDP socket listening on ' + address.address + ":" + address.port);
});

socket.on('message', function (message, remote) {
    console.log(remote.address + ':' + remote.port +' - ' + message);
});

socket.bind(port, function () {
	// join the multicast group
	socket.addMembership(host);
    socket.addMembership('230.1.2.4');
});
