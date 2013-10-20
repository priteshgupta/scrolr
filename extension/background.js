/*
// React when a browser action's icon is clicked.
chrome.browserAction.onClicked.addListener(function(tab) {
  //myscript.js is injected into the current page
  chrome.tabs.executeScript(null, {file: "myscript.js"}); 
});
*/

function plugin0()
{
	return document.getElementById('plugin0');
}
window.onload = function () {
  var plugin = plugin0();
  document.write("version = " + plugin.version);
  document.write("tracking = " + plugin.tracking);
  alert("hi!");
};

