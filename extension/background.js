/*
// React when a browser action's icon is clicked.
chrome.browserAction.onClicked.addListener(function(tab) {
  //myscript.js is injected into the current page
  chrome.tabs.executeScript(null, {file: "myscript.js"}); 
});
*/
function plugin0 (){
  return document.getElementById('plugin0');
}

function appendToDoc(text){
  console.log("adding text: " + text);
  var placeholder = document.getElementById('placeholder');
  placeholder.appendChild(document.createTextNode(text));
  placeholder.appendChild(document.createElement('br'));
}

window.onload = function () {
  //var plugin = plugin0();
  alert("hi!");
  //plugin.tracking = true;
  //plugin.initialize();
  //alert("initializing");
  //appendToDoc("version = " + plugin.version);
  //appendToDoc("tracking = " + plugin.tracking);
  //alert("should now be tracking: " + plugin.tracking);
};

