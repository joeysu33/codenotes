/*
html
<textarea name="txt" id="txt" cols="80" rows="10">
<button type="button" id="test">测试</button>

js
var test = document.querySelector('#test')
test.addEventListener('click', function () {
  var url = `/test?test=${txt.value}`   // 1. 发送一个GET请求
  var xhr = new XMLHttpRequest()
  xhr.onreadystatechange = function () {
    if (xhr.readyState === 4) {
      if ((xhr.status >= 200 && xhr.status < 300) || xhr.status === 304) {
        // 3. 客户端解析JSON，并执行
        var str = JSON.parse(xhr.responseText).test
        var node = `${str}`
        document.body.insertAdjacentHTML('beforeend', node)
      } else {
        console.log('error', xhr.responseText)
      }
    }
  }
  xhr.open('GET', url, true)
  xhr.send(null)
}, false)

express
*/

var express = require('express');
var router = express.Router();

router.get('/test', function (req, res, next) {
 // 2. 服务端解析成JSON后响应
  res.json({
    test: req.query.test
  })
})

