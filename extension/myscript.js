/*
   console.log("window.pageYOffset " + window.pageYOffset);
   console.log("document.documentElement.scrollTop " + document.documentElement.scrollTop);
   console.log("document.body.scrollTop " + document.body.scrollTop);
   var top = document.body.scrollTop;
   var n = 1; */
alert("asdf");

function createEmbed(width,height){
    var embed = document.createElement('embed');
    embed.setAttribute('id', "plugin0")
        embed.setAttribute('width',width);
    embed.setAttribute('height',height);
    embed.setAttribute('type',"application/x-scrolrplugin");
    //var div = document.getElementById(replaceid);
    //document.getElementsByTagName('body')[0].replaceChild(embed,div); 
    document.body.appendChild(embed);
}

function trackForN(n){
    plugin.tracking = true;
    setTimeout(function(){
            plugin.tracking = false;
            }, 1000*n);
    plugin.track();
}

createEmbed('0','0');
var plugin = document.getElementById("plugin0");

alert(plugin.version);
alert("is tracking: "+plugin.tracking);
//alert(plugin.getCurrentHeadDirection());
//alert(plugin.foundFile());

//plugin.track();
/*
setTimeout(function(){
        plugin.tracking = true;
        alert("now tracking = "+plugin.tracking);
        }, 5000);
*/
//plugin.testEvent();
/*setInterval(function(){
  window.scrollBy(0, plugin.getCurrentHeadDirection());
  }, 50);*/
