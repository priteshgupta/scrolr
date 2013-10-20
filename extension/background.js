var tracking = true;

function plugin0 (){
  return document.getElementById('plugin0');
}

function runTrackingLoop(){
  var plugin = plugin0();
  setInterval(function(){  
    if(tracking){
      var ret = plugin.track().split(" ", 2);
      console.log(ret);
      chrome.tabs.executeScript(null, 
        {
          code: "window.scrollBy(0, " + ret[1] + "); window.scrollBy(" + ret[0] + ", 0);"
        });
    }
  },50);
}

chrome.browserAction.onClicked.addListener(function(tab) {
  // toggle tracking and button icon
  if(tracking){
    tracking = false;
    chrome.browserAction.setIcon({path: "icon-32-grey.png"});
  } else {
    //plugin0().initialize();
    chrome.browserAction.setIcon({path: "icon-32.png"});
    tracking = true;
  }
});

window.onload = function () {
  var plugin = plugin0();
  console.log("initializing");
  plugin.initialize();
  tracking = true;
  console.log("starting tracking loop");
  runTrackingLoop();
};
