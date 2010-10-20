#include "bsuppliercommands.h"

const QString BSupplier::BServerId = "dcpbriefs";

// available commands (m_Input):
const QString BSupplier::CmdWatch = "watch ";
const QString BSupplier::CmdUnwatch = "unwatch ";
const QString BSupplier::CmdSwitchToggle = "toggle ";

// available responses (output):
const char* BSupplier::OutputBegin = "BEGIN";
const char* BSupplier::OutputEnd = "END";

// data identifiers:
const char* BSupplier::OutputName = "name";
const char* BSupplier::OutputWidgetTypeID = "widgetTypeID";
const char* BSupplier::OutputValueText = "valueText";
const char* BSupplier::OutputIcon = "icon";
const char* BSupplier::OutputToggle = "toggle";
const char* BSupplier::OutputTitleText = "titleText";
const char* BSupplier::OutputHelpId = "helpId";


