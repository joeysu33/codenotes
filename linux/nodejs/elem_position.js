/*!
get element of html position
getElementPosition is document position
,but getBoundingClientRect is client position
,that is to say: viewport position.
*/

function getElementPosition(e) {
    var x=0,y=0;
    while(e) {
        x += e.offsetLeft;
        y += e.offsetTop;
        e = e.offsetParent;
    }
    return {x:x, y:y};
}