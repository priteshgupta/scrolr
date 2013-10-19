#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for Scrolr Plugin
#
#\**********************************************************/

set(PLUGIN_NAME "ScrolrPlugin")
set(PLUGIN_PREFIX "SPL")
set(COMPANY_NAME "BuffaloHackers")

# ActiveX constants:
set(FBTYPELIB_NAME ScrolrPluginLib)
set(FBTYPELIB_DESC "ScrolrPlugin 1.0 Type Library")
set(IFBControl_DESC "ScrolrPlugin Control Interface")
set(FBControl_DESC "ScrolrPlugin Control Class")
set(IFBComJavascriptObject_DESC "ScrolrPlugin IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "ScrolrPlugin ComJavascriptObject Class")
set(IFBComEventSource_DESC "ScrolrPlugin IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID 90bac884-7946-5354-9a97-b9c130970fff)
set(IFBControl_GUID 2e1a5d76-8893-5b74-a893-1ad4620fee8f)
set(FBControl_GUID c6962235-9fce-5fab-b46f-c7faf4cb0f9c)
set(IFBComJavascriptObject_GUID df4145f7-6630-561a-b9d0-d738e4f01726)
set(FBComJavascriptObject_GUID 3546fcaf-22c1-5fa6-8803-5ccb96f954f7)
set(IFBComEventSource_GUID 4e008dd0-1b5c-560b-8006-72cd890bd862)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 1cb183bc-93bb-58ed-b1eb-a271017ec3e9)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 107e884f-9089-5fc1-a123-789aff086018)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "BuffaloHackers.ScrolrPlugin")
if ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "buffalohackers.com/ScrolrPlugin")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "buffalohackers.com/ScrolrPlugin_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )

# strings
set(FBSTRING_CompanyName "Buffalo Hackers")
set(FBSTRING_PluginDescription "Plugin for the Scrolr chrome extension")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2013 Buffalo Hackers")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}")
set(FBSTRING_ProductName "Scrolr Plugin")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "Scrolr Plugin")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "Scrolr Plugin_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-scrolrplugin")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 0)
set(FBMAC_USE_COCOA 0)
set(FBMAC_USE_COREGRAPHICS 0)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
