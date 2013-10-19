// React when a browser action's icon is clicked.
chrome.browserAction.onClicked.addListener(function(tab) {
  //myscript.js is injected into the current page
  chrome.tabs.executeScript(null, {file: "myscript.js"}); 
});