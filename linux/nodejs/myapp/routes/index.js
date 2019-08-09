var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

/*! GET number */
router.get('/:id(\\d+)', (req, res,next)=> {
    var params = req.params;
    var num = (params.id && parseInt(params.id, 10)) || 'NoNumber';
    res.render('number', {title:'Express', num:num});
});

module.exports = router;
