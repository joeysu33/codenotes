'use strict';
//const common = require('../common');
const assert = require('assert');
const http = require('http');
const net = require('net');
const util = require('util');

let outstanding_reqs = 0;

const server = http.createServer(function(req, res) {
  res.writeHead(200, [['content-type', 'text/plain']]);
  // add trailers
  res.addTrailers({ 'x-foo': 'bar' });
  res.end('stuff\n');
});
server.listen(8000);


// First, we test an HTTP/1.0 request.
server.on('listening', function() {
  const c = net.createConnection(this.address().port);
  let res_buffer = '';

  c.setEncoding('utf8');

  c.on('connect', function() {
    outstanding_reqs++;
    c.write('GET / HTTP/1.0\r\n\r\n');
  });

  c.on('data', function(chunk) {
    res_buffer += chunk;
  });

  c.on('end', function() {
    console.log(`TEST:HTTP1.0 Request:${res_buffer}`);
    console.log("++++++++++++++++++++++++++");
    c.end();
    assert.ok(
      !/x-foo/.test(res_buffer),
      `Trailer in HTTP/1.0 response. Response buffer: ${res_buffer}`
    );
    outstanding_reqs--;
    if (outstanding_reqs === 0) {
      server.close();
      process.exit();
    }
  });
});

// Now, we test an HTTP/1.1 request.
server.on('listening', function() {
  const c = net.createConnection(this.address().port);
  let res_buffer = '';
  let tid;

  c.setEncoding('utf8');

  c.on('connect', function() {
    outstanding_reqs++;
    c.write('GET / HTTP/1.1\r\n\r\n');
    //tid = setTimeout(common.mustNotCall(), 2000, 'Couldn\'t find last chunk.');
  });

  c.on('data', function(chunk) {
    res_buffer += chunk;
    if (/0\r\n/.test(res_buffer)) { // got the end.
        console.log(`TEST:HTTP/1.1 Request:${res_buffer}`);
      outstanding_reqs--;
      //clearTimeout(tid);
      assert.ok(
        /0\r\nx-foo: bar\r\n\r\n$/.test(res_buffer),
        `No trailer in HTTP/1.1 response. Response buffer: ${res_buffer}`
      );
      if (outstanding_reqs === 0) {
        server.close();
        process.exit();
      }
    }
  });
});

// Now, see if the client sees the trailers.
server.on('listening', function() {
  http.get({
    port: this.address().port,
    path: '/hello',
    headers: {}
  }, function(res) {
    res.on('end', function() {
    console.log("TEST:client see Trailes: "+ JSON.stringify(res.trailers));
      assert.ok('x-foo' in res.trailers,
                `${util.inspect(res.trailers)} misses the 'x-foo' property`);
      outstanding_reqs--;
      if (outstanding_reqs === 0) {
        server.close();
        process.exit();
      }
    });
    res.resume();
  });
  outstanding_reqs++;
});
