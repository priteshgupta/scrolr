console.log("window.pageYOffset " + window.pageYOffset);
console.log("document.documentElement.scrollTop " + document.documentElement.scrollTop);
console.log("document.body.scrollTop " + document.body.scrollTop);
var top = document.body.scrollTop;
var n = 1;
setInterval(function(){
  window.scrollBy(0, 1);
}, 20)

