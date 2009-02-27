#include "dcpappletmetadata.h"

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
}

QString
DcpAppletMetadata::icon() const
{
}

QString
DcpAppletMetadata::appletBinary() const
{
}

