var tracking = false;


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
    setInterval(function(){  
        if(tracking){
            var ret = plugin.track();
            console.log(ret);
            chrome.tabs.executeScript(null, {code: "window.scrollBy(0, "+ret+");"});
        }
    },50);
}

chrome.browserAction.onClicked.addListener(function(tab) {
    if(tracking){
        tracking = false;
        chrome.browserAction.setIcon({path: "icon-32-grey.png"});
    } else {
        tracking = true;
        chrome.browserAction.setIcon({path: "icon-32.png"});
        //runTrackingLoop();
    }
});

window.onload = function () {
    var plugin = plugin0();
    //alert("ready?");
    console.log("initializing");
    plugin.initialize();
    tracking = true;
    console.log("starting tracking loop");
    runTrackingLoop();
    //appendToDoc("version = " + plugin.version);
    //appendToDoc("tracking = " + plugin.tracking);
};
