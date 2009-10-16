#include "maintranslations.h"

const DcpCategoryInfo DcpMain::CategoryInfos[] = {
    {
		"qtn_sett_main_look", "Look & Feel",
    	"Look & Feel",
    	Pages::LOOKANDFEEL
    },
    {
        "qtn_sett_main_sound", "Sounds",
		"Sound",
		Pages::SOUND
    },
    {
        "qtn_sett_main_connectivity", "Connectivity",
        "Connectivity",
        Pages::CONNECTIVITY
    },
    {
        "qtn_sett_main_region", "Regional settings",
		"Regional settings",
		Pages::REGIONALSETTING
	},
	{
	    "qtn_sett_main_device", "Device utilities",
		"Device utilities",
		Pages::DEVICEUTILITIES
	},
	{
	    "qtn_sett_main_data", "Device system",
		"Device system",
		Pages::DEVICESYSTEM
	},
	{
	    "qtn_sett_main_combined", "Accounts & Applications",
		"Accounts & Applications",
		Pages::ACCOUNTSANDAPPLICATIONS
	},
	{ 0, 0, 0, Pages::NOPAGE }
};


const char* DcpMain::settingsTitleId = "qtn_sett_main_title";
const char* DcpMain::settingsTitleDefault = "Settings";

const char* DcpMain::mostRecentUsedTitleId = "qtn_sett_main_most";
const char* DcpMain::mostRecentUsedTitleDefault = "Most recently used";

const char* DcpMain::quitMenuItemTextId = "qtn_comm_exit";
const char* DcpMain::quitMenuItemTextDefault = "Exit";


