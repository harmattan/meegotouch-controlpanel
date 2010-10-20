#ifndef BSUPPLIERCOMMANDS
#define BSUPPLIERCOMMANDS

#include <QString>

namespace BSupplier
{

// server id:
extern const QString BServerId;

// available commands (m_Input):
extern const QString CmdWatch;
extern const QString CmdUnwatch;
extern const QString CmdSwitchToggle;

// available responses (output):
extern const char* OutputBegin;
extern const char* OutputEnd;

// data identifiers:
extern const char* OutputName;
extern const char* OutputWidgetTypeID;
extern const char* OutputValueText;
extern const char* OutputIcon;
extern const char* OutputToggle;
extern const char* OutputTitleText;
extern const char* OutputHelpId;


}

#endif // BSUPPLIERCOMMANDS

