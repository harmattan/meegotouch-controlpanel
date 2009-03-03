#include "dcpappletmetadata.h"

enum  {
    KeyCategory = 0,
    KeyOnPicture,
    KeyOffPicture,
    KeyDisabledPicture,
    KeyCount
};

const QString Keys[KeyCount] = {
    "DCP/Category",
    "DCP/OnPicture",
    "DCP/OffPicture",
    "DCP/DisabledPicture"
};

DcpAppletMetadata::DcpAppletMetadata(const QString& filename) 
    : DuiDesktopEntry(filename)
{
}

DcpAppletMetadata::~DcpAppletMetadata()
{
}

bool
DcpAppletMetadata::isValid()
{
    return false;
}

QString
DcpAppletMetadata::category() const
{
    return value(Keys[KeyCategory]).toString();
}

QString
DcpAppletMetadata::icon() const
{
    return "";
}

QString
DcpAppletMetadata::appletBinary() const
{
    return "";
}

