require('net').createServer(function(sock) {
    sock.on('data', function(data) {
        sock.write('HTTP/1.1 200 OK\r\n');
        sock.write('Transfer-Encoding: chunked\r\n');
        sock.write('\r\n');

        //chunk
        sock.write('b\r\n'); //hex code
        sock.write('01234567890\r\n');

        //chunk
        sock.write('5\r\n');
        sock.write('12345\r\n');

        //chunk
        sock.write('12\r\n')
        sock.write('This is my movies!\r\n'); //18bytes

        //end of chunk
        sock.write('0\r\n');
        sock.write('\r\n');
    });
}).listen(9090, '127.0.0.1');
