#ifndef QTCOLORIZECONSTANTS_H
#define QTCOLORIZECONSTANTS_H



#include <QtGlobal>



namespace QtColorize
{
namespace Constants
{



const char MENU_ID[]          = "QtColorize.Menu";
const char CONTEXT_MENU_ID[]  = "QtColorize.ContextMenu";
const char ACTION_TOGGLE_ID[] = "QtColorize.ActionToggle";
const char ACTION_GREEN_ID[]  = "QtColorize.ActionGreen";
const char ACTION_RED_ID[]    = "QtColorize.ActionRed";
const char ACTION_REMOVE_ID[] = "QtColorize.ActionRemove";



const char CORE_SETTINGS_GROUP[] = "QtColorizePlugin";

const char SETTING_GREEN_COLOR[] = "GreenColor";
const char SETTING_RED_COLOR[]   = "RedColor";
const char SETTING_ALIGNMENT[]   = "Alignment";

const char    SETTING_GREEN_COLOR_DEFAULT[] = "#DDFFDD";
const char    SETTING_RED_COLOR_DEFAULT[]   = "#FFDDDD";
const quint16 SETTING_ALIGNMENT_DEFAULT     = 100;



const char QTCOLORIZE_ROW_ID[] = "QtColorize.Row";



const char ICON_QTCOLORIZEPLUGIN_OPTIONS[] = ":/qtcolorizeplugin/assets/images/optionspageicon.png";



} // namespace Constants
} // namespace QtColorize



#endif // QTCOLORIZECONSTANTS_H
