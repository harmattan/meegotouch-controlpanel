#include "maintranslations.h"

const DcpCategoryInfo DcpMain::CategoryInfos[] = {
    {
		"qtn_sett_main_seeing", "Look & Feel",
    	"Look & Feel",
    	Pages::LOOKANDFEEL
    },
    {
        "qtn_sett_main_sound", "Sound",
		"Sound",
		Pages::SOUND
    },
    {
        "qtn_sett_main_connectivity", "Connectivity",
        "Connectivity",
        Pages::CONNECTIVITY
    },
    {
        "qtn_sett_main_regional", "Regional settings",
		"Regional settings",
		Pages::REGIONALSETTING
	},
	{
	    "qtn_sett_main_device", "Device utilities",
		"Device utilities",
		Pages::DEVICEUTILITIES
	},
	{
	    "qtn_sett_resetsettings", "Device system",
		"Device system",
		Pages::DEVICESYSTEM
	},
	{
	    "qtn_sett_main_accountandaplication", "Accounts & Applications",
		"Accounts & Applications",
		Pages::ACCOUNTSANDAPPLICATIONS
	},
	{ 0, 0, 0, Pages::NOPAGE }
};


const char* DcpMain::settingsTitleId = "qtn_sett_title";
const char* DcpMain::settingsTitleDefault = "Settings";

const char* DcpMain::mostRecentUsedTitleId = "qtn_sett_main_most";
const char* DcpMain::mostRecentUsedTitleDefault = "Most recent used";

const char* DcpMain::quitMenuItemTextId = "qtn_quit_main_text";
const char* DcpMain::quitMenuItemTextDefault = "Exit";


