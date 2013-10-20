/**********************************************************\

  Auto-generated ScrolrPluginAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "ScrolrPluginAPI.h"


//Edited by Mack
#include "Tracker.h"
#include <string>
#include <boost/thread.hpp>

using std::string;


///////////////////////////////////////////////////////////////////////////////
/// @fn FB::variant ScrolrPluginAPI::echo(const FB::variant& msg)
///
/// @brief  Echos whatever is passed from Javascript.
///         Go ahead and change it. See what happens!
///////////////////////////////////////////////////////////////////////////////
FB::variant ScrolrPluginAPI::echo(const FB::variant& msg)
{
    static int n(0);
    fire_echo("So far, you clicked this many times: ", n++);

    // return "foobar";
    return msg;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn ScrolrPluginPtr ScrolrPluginAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
ScrolrPluginPtr ScrolrPluginAPI::getPlugin()
{
    ScrolrPluginPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

// Read/Write property testString
std::string ScrolrPluginAPI::get_testString()
{
    return m_testString;
}

void ScrolrPluginAPI::set_testString(const std::string& val)
{
    m_testString = val;
}

// Read-only property version
std::string ScrolrPluginAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

int ScrolrPluginAPI::getCurrentYOffset(){
    return m_tracker.yOffset;
}

int ScrolrPluginAPI::getCurrentXOffset(){
    return m_tracker.xOffset;
}

string ScrolrPluginAPI::track(){
    return m_tracker.track();
}

int ScrolrPluginAPI::initialize(){
    m_tracker.initialize();
    return 0;
}

bool ScrolrPluginAPI::foundFile(){
    return m_tracker.m_foundFile;
}

bool ScrolrPluginAPI::get_isTracking(){
    return m_tracker.m_isTracking;
}

void ScrolrPluginAPI::set_isTracking(bool t){
    m_tracker.m_isTracking = t;
}
