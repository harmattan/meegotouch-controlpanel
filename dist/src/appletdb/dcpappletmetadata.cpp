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

bool
DcpAppletMetadata::isValid() const
{
    return desktopEntry()->isValid();
}

// TODO solve reloading XXX
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

/*
QString DcpAppletMetadata::widgetType()
{

    return desktopEntry()->value(Keys[KeyWidgetType]).toString();
}
*/


int DcpAppletMetadata::widgetTypeID() const
{
    int btypeid = brief()->widgetTypeID();
    if (btypeid != -1) return btypeid;

  // old way, TODO consider removing it and forcing the applets to supply a widgettype
  QString type = desktopEntry()->value(Keys[KeyWidgetType]).toString();

  for(int i=0; i<WIDGETN; i++)
    if (WIDGETNAME[i]==type)
      return i;

  return -1;  //error

}

Qt::Alignment DcpAppletMetadata::align() const
{
    QString align = desktopEntry()->value(Keys[KeyAlign]).toString().toUpper();
    if (align == "LEFT")
        return Qt::AlignLeft;
    if (align == "RIGHT")
        return Qt::AlignRight;

    return brief()->align();
}

bool DcpAppletMetadata::toggle() const
{
    return brief()->toggle();
}

/*
bool DcpAppletMetadata::smallToggle()
{
  if (value(Keys[KeySmallToggle]).toString() == "TRUE")
    return true;

  return false;
}
*/

QString DcpAppletMetadata::text1() const
{
    QString id = desktopEntry()->value(Keys[KeyNameId]).toString();
    QString name = desktopEntry()->value(Keys[KeyName]).toString();
//    QString catalog = value(Keys[KeyNameCatalog]).toString();
    return DuiLocale::trid(qPrintable(id), qPrintable(name));
}

QString DcpAppletMetadata::text2() const
{
    return brief()->valueText();
}

QString DcpAppletMetadata::image() const
{
    return brief()->image();
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
/*
QString DcpAppletMetadata::settingsValue()
{
    QSettings settings("Maemo", "DuiControlPanel");
    QString val = "";
    QString confKey = "";
    QString key = Keys[KeyValuePath];
    if (contains(key))
     {
        confKey = value(key).toString();
        val = settings.value(confKey).toString();
     }
    qDebug() << "DCP" << key << confKey << val;
    return val;
}
*/

DcpAppletIf* DcpAppletMetadata::applet() const
{
    if (d->m_AppletLoader == NULL){
        d->m_AppletLoader = new DcpAppletLoader(this);
    }
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
        } else {
            qWarning() << "Failed to load brief for applet:" << name();
            d->m_Brief = new DcpBrief();
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

