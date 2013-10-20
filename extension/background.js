
function plugin0 (){
  return document.getElementById('plugin0');
}

function appendToDoc(text){
  console.log("adding text: " + text);
  var placeholder = document.getElementById('placeholder');
  placeholder.appendChild(document.createTextNode(text));
  placeholder.appendChild(document.createElement('br'));
}

function runTrackingLoop(){
  var plugin = plugin0();
  while(plugin.tracking){
    var ret = plugin.track();
    console.log(ret);
    chrome.tabs.executeScript(null, {code: "window.scrollBy(0, "+ret+");"});
  }
}

window.onload = function () {
  var plugin = plugin0();
  alert("ready?");
  console.log("initializing");
  //plugin.initialize();
  console.log("starting tracking loop");
  //runTrackingLoop();
  //appendToDoc("version = " + plugin.version);
  //appendToDoc("tracking = " + plugin.tracking);
};

chrome.browserAction.onClicked.addListener(function(tab) {
  var plugin = plugin0();
  if(plugin.tracking){
    plugin.tracking = false;
    chrome.browserAction.setIcon({path: "icon-32-grey.png"});
  } else {
    plugin.tracking = true;
    chrome.browserAction.setIcon({path: "icon-32.png"});
    //runTrackingLoop();
  }
});

