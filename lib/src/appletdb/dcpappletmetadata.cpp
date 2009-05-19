#include <QDateTime>
#include "dcpappletmetadata.h"
#include "dcpapplet.h"
#include <duilocale.h>
#include <QDebug>
#include "dcpappletmetadata_p.h"
#include "dcpwidgettypes.h"
#include <DuiDesktopEntry>
#include "dcpappletloader.h"
#include "dcpbrief.h"
#include "dcpappletif.h"

enum  {
    KeyCategory = 0,
    KeyOrder,
    KeyOnPicture,
    KeyOffPicture,
    KeyDisabledPicture,

    KeyWidgetType,
    KeyAlign,
    KeyToggle,
    KeySmallToggle,

    KeyText2,
    KeyImage,
    KeyButtonCSS,
    KeyLabel1CSS,
    KeyLabel2CSS,
    KeyUsage,
    KeyBinary,

    KeyName,
    KeyNameId,
    KeyNameCatalog,

    KeyValuePath,
    KeyCount,
};

const QString Keys[KeyCount] = {
    "DCP/Category",
    "DCP/Order",
    "DCP/OnPicture",
    "DCP/OffPicture",
    "DCP/DisabledPicture",

    "DCP/WidgetType",
    "DCP/Align",
    "DCP/Toggle",
    "DCP/SmallToggle",

    "DCP/Text2",
    "DCP/Image",
    "DCP/ButtonCSS",
    "DCP/Label1CSS",
    "DCP/Label2CSS",
    "DCP/Usage",
    "DUI/X-DUIApplet-Applet",

    "Desktop Entry/Name",
    "Desktop Entry/X-logical-id",
    "Desktop Entry/X-translation-catalog",
    "DCP/ValuePath"
};


DcpAppletMetadataPrivate::DcpAppletMetadataPrivate()
    : m_AppletLoader(NULL),
      m_Brief(NULL),
      m_DesktopEntry(NULL)
{
}

DcpAppletMetadataPrivate::~DcpAppletMetadataPrivate()
{
    if (m_AppletLoader) delete m_AppletLoader;
    if (m_Brief) delete m_Brief;
    if (m_DesktopEntry) delete m_DesktopEntry;
}


DcpAppletMetadata::DcpAppletMetadata(const QString& filename)
    : d (new DcpAppletMetadataPrivate)
{
    d->m_DesktopEntry = new DuiDesktopEntry(filename);
}

DcpAppletMetadata::~DcpAppletMetadata()
{
    delete d;
}

// TODO XXX rename
bool
DcpAppletMetadata::isValid() const
{
    return desktopEntry()->isValid();
}

// TODO XXX rename
bool
DcpAppletMetadata::isModified() const
{
    QFileInfo info(d->m_FileInfo.fileName());
    bool modified = info.lastModified() >  d->m_FileInfo.lastModified();
    d->m_FileInfo = info;
    return modified;
}

QString
DcpAppletMetadata::category() const
{
    return desktopEntry()->value(Keys[KeyCategory]).toString();
}

/*
QString
DcpAppletMetadata::icon() const
{
    return brief()->icon();
}
*/

QString
DcpAppletMetadata::binary() const
{
    return desktopEntry()->value(Keys[KeyBinary]).toString();
}

QString
DcpAppletMetadata::fullBinary() const
{
    return DcpApplet::Lib + binary();
}

int DcpAppletMetadata::widgetTypeID() const
{
    if (brief() != NULL) {
        return brief()->widgetTypeID();
    }

  // old way, TODO consider removing it and forcing the applets to supply a widgettype
  QString type = desktopEntry()->value(Keys[KeyWidgetType]).toString();

  for(int i=0; i<WIDGETN; i++)
    if (WIDGETNAME[i]==type)
      return i;

  return DCPLABEL2;  //default

}

Qt::Alignment DcpAppletMetadata::align() const
{
    if (brief()){
        return brief()->align();
    }

    // old way, try desktop file
    QString align = desktopEntry()->value(Keys[KeyAlign]).toString().toUpper();
    if (align == "LEFT")
        return Qt::AlignLeft;
    if (align == "RIGHT")
        return Qt::AlignRight;

    qWarning() << Q_FUNC_INFO << "no data"; // default
    return Qt::AlignLeft; 
}

bool DcpAppletMetadata::toggle() const
{
    if (brief()){
        return brief()->toggle();
    }

    qWarning() << Q_FUNC_INFO << "no brief"; // default
    return false;
}

QString DcpAppletMetadata::text1() const
{
    QString id = desktopEntry()->value(Keys[KeyNameId]).toString();
    QString name = desktopEntry()->value(Keys[KeyName]).toString();
//    QString catalog = value(Keys[KeyNameCatalog]).toString();
    return DuiLocale::trid(qPrintable(id), qPrintable(name));
}

QString DcpAppletMetadata::text2() const
{
    if (brief())
        return brief()->valueText();

    // old way, TODO change it to return QString() if test data is not needed
    return desktopEntry()->value(Keys[KeyText2]).toString();
}

QString DcpAppletMetadata::image() const
{
    if (brief())
        return brief()->image();

    // old way
    return desktopEntry()->value(Keys[KeyImage]).toString();
}

int DcpAppletMetadata::usage() const
{
    // TODO implement
    return desktopEntry()->value(Keys[KeyUsage]).toInt();
}

int DcpAppletMetadata::order() const
{
    return desktopEntry()->value(Keys[KeyOrder]).toInt();
}

DcpAppletIf* DcpAppletMetadata::applet() const
{
    if (d->m_AppletLoader == NULL){
        d->m_AppletLoader = new DcpAppletLoader(this);
    }
//    qDebug() << Q_FUNC_INFO << d->m_AppletLoader->errorMsg() << fullBinary();
    return d->m_AppletLoader->applet();
}

DuiDesktopEntry* DcpAppletMetadata::desktopEntry() const
{
    Q_ASSERT (d->m_DesktopEntry);
    return d->m_DesktopEntry;
}

DcpBrief* DcpAppletMetadata::brief() const
{
    if (d->m_Brief == NULL) {
        if (applet() != NULL) {
            d->m_Brief = applet()->constructBrief();
            if (d->m_Brief != NULL){
                connect (d->m_Brief, SIGNAL(valuesChanged()),
                         this, SIGNAL(briefChanged()));
            }
        }
    }
    return d->m_Brief;
}

// TODO XXX rename
QString DcpAppletMetadata::name() const
{
    return desktopEntry()->name();
}

// TODO XXX rename
QString DcpAppletMetadata::fileName() const
{
    return desktopEntry()->fileName();
}

