/*
 * 标准数据流的主要事件
 * data (read)
 * end (read)
 * finish (write)
 * error (error)
*/

var fs = require('fs');
var rs = fs.createReadStream('163.txt')

var data;
var i=0;
rs.setEncoding('utf-8');
rs.on('data', (chunk) => {
    data += chunk;
    i++;
    console.log("receive chunk:"+i);
    //console.log("receive chunk:"+chunk);
});

rs.on('end', () => { console.log("finish"); });
rs.on('error', (e) => { console.error(e); });


