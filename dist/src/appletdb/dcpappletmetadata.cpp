#include <QDateTime>
#include "dcpappletmetadata.h"
#include "dcpapplet.h"
enum  {
    KeyCategory = 0,
    KeyOrder,
    KeyOnPicture,
    KeyOffPicture,
    KeyDisabledPicture,

    KeyWidgetType,
    KeyText1,
    KeyText2,
    KeyImage,
    KeyButtonCSS,
    KeyLabel1CSS,
    KeyLabel2CSS,
    KeyBinary,
    KeyCount
};

const QString Keys[KeyCount] = {
    "DCP/Category",
    "DCP/Order",
    "DCP/OnPicture",
    "DCP/OffPicture",
    "DCP/DisabledPicture",
    
    "DCP/WidgetType",
    "DCP/Text1",
    "DCP/Text2",
    "DCP/Image",
    "DCP/ButtonCSS",
    "DCP/Label1CSS",
    "DCP/Label2CSS",
    "DUI/X-DUIApplet-Applet"
};

DcpAppletMetadata::DcpAppletMetadata(const QString& filename) 
    : DuiDesktopEntry(filename), m_FileInfo(QFileInfo(filename))
{
   
}

DcpAppletMetadata::~DcpAppletMetadata()
{
}

bool
DcpAppletMetadata::isValid()
{
    return DuiDesktopEntry::isValid();
}

bool
DcpAppletMetadata::isModified()
{
    QFileInfo info(m_FileInfo.fileName());
    bool modified = info.lastModified() >  m_FileInfo.lastModified();
    m_FileInfo = info;
    return modified;
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
DcpAppletMetadata::binary() const
{
    return value(Keys[KeyBinary]).toString();
}

QString
DcpAppletMetadata::fullBinary() const
{
    return DcpApplet::Lib + binary();
}

QString DcpAppletMetadata::widgetType()
{
    return value(Keys[KeyWidgetType]).toString();
}

QString DcpAppletMetadata::text1()
{
    return value(Keys[KeyText1]).toString();
}

QString DcpAppletMetadata::text2()
{
    return value(Keys[KeyText2]).toString();
}

QString DcpAppletMetadata::image()
{
    return value(Keys[KeyImage]).toString();
}

QString DcpAppletMetadata::buttonCSS()
{
    return value(Keys[KeyButtonCSS]).toString();
}

QString DcpAppletMetadata::label1CSS()
{
    return value(Keys[KeyLabel1CSS]).toString();
}

QString DcpAppletMetadata::label2CSS()
{
    return value(Keys[KeyLabel2CSS]).toString();
}

int DcpAppletMetadata::order()
{
    return value(Keys[KeyOrder]).toInt();
}


