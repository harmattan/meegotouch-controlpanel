/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include <QDateTime>
#include "dcpappletmetadata.h"
#include "dcpapplet.h"
#include <duilocale.h>
#include <QDebug>
#include "dcpappletmetadata_p.h"
#include <DcpWidgetTypes>
#include <DuiDesktopEntry>

#include "dcpappletdb.h"
#include "dcpappletloader.h"
#include "dcpbrief.h"
#include "dcpappletif.h"
#include "dcpwidget.h"

#include "dcpmostusedcounter.h"

#define DEBUG
#include "dcpdebug.h"

enum  {
    KeyCategory = 0,
    KeyOrder,
    KeyOnPicture,
    KeyOffPicture,
    KeyDisabledPicture,

    KeyWidgetType,
    KeyAlign,
    KeyToggleIconId,

    KeyText2,
    KeyImage,
    KeyUsage,
    KeyBinary,
    KeyDslFilename,
    KeyApplicationCommand,

    KeyName,
    KeyNameId,
    KeyNameCatalog,

    KeyPart,
    KeyUnique,
    KeyParent,
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
    "DCP/ToggleIconId",

    "DCP/Text2",
    "DCP/Image",
    "DCP/Usage",
    "DUI/X-DUIApplet-Applet",
    "DUI/X-DUIApplet-Dslfile",
    "DUI/X-DUIApplet-ApplicationCommand",
    

    "Desktop Entry/Name",
    "Desktop Entry/X-logical-id",
    "Desktop Entry/X-translation-catalog",
    "DCP/Part",
    "DCP/Unique",
    "DCP/Parent"
};


DcpAppletMetadataPrivate::DcpAppletMetadataPrivate()
    : m_AppletLoader(0),
      m_Brief(0),
      m_DesktopEntry(0),
      m_Parent(0),
      m_Counter(-1),
      m_FileName(""),
      m_BinaryDir(APPLET_LIBS)
{
    if (!m_BinaryDir.endsWith('/')) m_BinaryDir += '/';
}

DcpAppletMetadataPrivate::~DcpAppletMetadataPrivate()
{
    if (m_AppletLoader) m_AppletLoader->deleteLater();
    if (m_Brief) m_Brief->deleteLater();
    if (m_DesktopEntry) delete m_DesktopEntry;
}

DcpAppletMetadata::DcpAppletMetadata(const QString& filename)
    : d (new DcpAppletMetadataPrivate)
{
    DCP_DEBUG ("*** filename = '%s'", DCP_STR(filename));

    d->m_FileName = filename;
    d->m_DesktopEntry = new DuiDesktopEntry(d->m_FileName);
    d->m_GconfKeyUsage = MOSTUSEDCOUNTER_GCONFKEY  + QFileInfo(d->m_FileName).baseName();

//	qDebug() << MostUsedCounter::instance()->get(d->m_FileName);
//	MostUsedCounter::instance()->clear(d->m_FileName);
//	qDebug() << MostUsedCounter::instance()->get(d->m_FileName);
}

DcpAppletMetadata::~DcpAppletMetadata()
{
//	save();
    delete d;
}

// TODO XXX rename
bool
DcpAppletMetadata::isValid() const
{
    DCP_DEBUG ("Returning %s for '%s'", 
            desktopEntry()->isValid() ? "true" : "false",
            DCP_STR (binary()));

    return desktopEntry()->isValid();
}

// TODO XXX rename
bool DcpAppletMetadata::isModified() const
{
    QFileInfo info(d->m_FileName);
    bool modified = info.lastModified() >  d->m_FileInfo.lastModified();
    d->m_FileInfo = info;
    return modified;
}

QString DcpAppletMetadata::category() const
{
    return desktopEntryStr(KeyCategory);
}

QString DcpAppletMetadata::binaryDir() const
{
    return d->m_BinaryDir;
}

void DcpAppletMetadata::setBinaryDir(const QString& dir)
{
    d->m_BinaryDir = dir;
}

QString 
DcpAppletMetadata::binary() const
{
    return desktopEntryStr (KeyBinary);
}

QString 
DcpAppletMetadata::dslFilename () const
{
    return desktopEntryStr (KeyDslFilename);
}

QString 
DcpAppletMetadata::applicationCommand () const
{
    return desktopEntryStr (KeyApplicationCommand);
}

bool
DcpAppletMetadata::hasApplicationCommand () const
{
    return !desktopEntryStr(KeyApplicationCommand).isEmpty();
}



/*
 * Returns the full path of the applet plugin filename, that is the name of the
 * shared object, that contains the applet binary program or if the 
 * "X-DUIApplet-Applet" field of the desktop file is empty returns the empty
 * string.
 */
QString
DcpAppletMetadata::fullBinary () const
{
    QString filename = binary();

    if (filename.isEmpty())
        return filename;

    return binaryDir () + filename;
}

QString DcpAppletMetadata::parentName() const
{
    return desktopEntryStr(KeyParent);
}

int DcpAppletMetadata::widgetTypeID() const
{
  if (brief() != 0) {
      return brief()->widgetTypeID();
  }

  QString type = desktopEntryStr(KeyWidgetType);

  for(int i=0; i<WIDGETN; i++)
    if (WIDGETNAME[i]==type) {
      return i;
    }

  qWarning() << "widgettype is unspecified for " << name();
  return DCPLABEL2;  //default
}

Qt::Alignment DcpAppletMetadata::align() const
{
    if (brief()){
        return brief()->align();
    }

    // old way, try desktop file
    QString align = desktopEntryStr(KeyAlign).toUpper();
    if (align == "LEFT")
        return Qt::AlignLeft;
    if (align == "RIGHT")
        return Qt::AlignRight;

    qWarning() << Q_FUNC_INFO << "no data"; // default
    return Qt::AlignLeft;
}

DcpAppletMetadata* DcpAppletMetadata::parent() const
{
    return d->m_Parent;
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
    QString id = desktopEntryStr(KeyNameId);
    QString name = desktopEntryStr(KeyName);
//    QString catalog = value(Keys[KeyNameCatalog]).toString();
    if (qtTrId(qPrintable(id)) == id)
        return ("!! " + name);
    else
        return qtTrId(qPrintable(id));
}

QString DcpAppletMetadata::text2() const
{
    if (brief())
        return brief()->valueText();

    // static way
    return desktopEntryStr(KeyText2);
}

QString DcpAppletMetadata::image() const
{
    if (brief())
        return brief()->image();

    // static way
    return desktopEntryStr(KeyImage);
}

QString DcpAppletMetadata::toggleIconId() const
{
    if (brief())
        return brief()->toggleIconId();

    // static way
    return desktopEntryStr(KeyToggleIconId);
}

/*!
 * \brief A slot for the inter plugin activation.
 * \param name The name of the other applet to activate.
 * 
 * \details This slot will activate an other applet. First the function will
 * find the applet using the applet database then it will emit a signal for it,
 * so it is going to be started.
 */
bool 
DcpAppletMetadata::activatePluginByName (
        int            refererID,
        const QString &name) const
{
    DcpAppletMetadata  *otherApplet;
    DcpWidget          *senderWidget = qobject_cast<DcpWidget *> (sender());

    Q_UNUSED (refererID);
    Q_ASSERT (senderWidget != NULL);
   
    DCP_WARNING ("Want to start '%s' by %s/%d", 
            DCP_STR (name),
            DCP_STR (this->name()),
            senderWidget->getWidgetId());

    otherApplet = DcpAppletDb::instance()->applet (name);
    if (otherApplet) {
        DCP_DEBUG ("Emitting %p->activateWithReferer (%s, %d)", 
                otherApplet,
                DCP_STR (this->name()), 
                senderWidget->getWidgetId());
        emit otherApplet->activateWithReferer (
                this->name(), senderWidget->getWidgetId());

        return true;
    }
        
    DCP_WARNING ("Applet with name '%s' not found.", DCP_STR (name));
    return false;
}

void DcpAppletMetadata::setToggle(bool checked)
{
    if (brief()) {
        brief()->setToggle(checked);
    } else {
        qWarning("Can not set toggle state for the applet %s",
                 qPrintable(d->m_FileName));
    }
}

bool DcpAppletMetadata::isUnique() const
{
    DCP_DEBUG ("Returning %s for %s",
            !desktopEntryStr(KeyUnique).isEmpty() ? "true" : "false",
            DCP_STR (binary()));
    return !desktopEntryStr(KeyUnique).isEmpty();
}

QString DcpAppletMetadata::part() const
{
    return desktopEntryStr(KeyPart);
}

/*!
 * \brief Calls the applet and returns the partid set for this desktop file. 
 *
 * This function will take the "DCP/Part" key and call the 
 * "int partID(const QString& partStr)" function of the plugin to get the
 * widgetId for the first/main widget. If the applet is not available the 
 * function will return -1, that is an invalid widgetId.
 */
int 
DcpAppletMetadata::getMainWidgetId () const
{
    DCP_DEBUG ("");
    if (!applet())
        return -1;

    return applet()->partID (part());
}

int DcpAppletMetadata::usage () const
{
    // TODO implement
    //return desktopEntry()->value(Keys[KeyUsage]).toInt() + d->m_Counter;
    return MostUsedCounter::instance()->get(d->m_GconfKeyUsage);
}

int DcpAppletMetadata::order() const
{
    return desktopEntry()->value(Keys[KeyOrder]).toInt();
}

DcpAppletIf *
DcpAppletMetadata::applet() const
{
    if (d->m_Parent)
        return d->m_Parent->applet();

    if (d->m_AppletLoader == 0) {
        d->m_AppletLoader = new DcpAppletLoader (this);
        
        #ifdef WARNING
        if (d->m_AppletLoader->applet() == 0) {
            qDebug() << d->m_AppletLoader->errorMsg() << "for" << binary();
            DCP_WARNING ("Failed to load applet file '%s': %s",
                    DCP_STR (fullBinary()),
                    DCP_STR (d->m_AppletLoader->errorMsg()));
        } else {
            DCP_DEBUG ("Loaded applet file '%s'", DCP_STR(fullBinary()));
        }
        #endif
    }

    return d->m_AppletLoader->applet();
}

DuiDesktopEntry* DcpAppletMetadata::desktopEntry() const
{
    Q_ASSERT (d->m_DesktopEntry);

    return d->m_DesktopEntry;
}

DcpBrief *
DcpAppletMetadata::brief () const
{
    DCP_DEBUG ("Brief for '%s' id is %d", DCP_STR (name()), getMainWidgetId());
    if (d->m_Brief == 0 && applet() != 0) {
        d->m_Brief = applet()->constructBrief(getMainWidgetId());
        if (d->m_Brief != 0)
            connect (d->m_Brief, SIGNAL (valuesChanged ()), 
                    this, SIGNAL (briefChanged ()));
    }

    return d->m_Brief;
}


// TODO XXX rename
QString DcpAppletMetadata::name() const
{
    return desktopEntry()->name().trimmed();
}

// TODO XXX rename
QString DcpAppletMetadata::fileName() const
{
    return desktopEntry()->fileName();
}

QString DcpAppletMetadata::desktopEntryStr(int id) const
{
    return desktopEntry()->value(Keys[id]).trimmed();
}

void DcpAppletMetadata::cleanup()
{
    if (d->m_AppletLoader)
        d->m_AppletLoader->deleteLater();
    d->m_AppletLoader = 0;
}
void DcpAppletMetadata::setParent(DcpAppletMetadata *parent)
{
    d->m_Parent = parent;
}

void DcpAppletMetadata::slotClicked()
{
//Q_ASSERT(0);
		//add
	//d->m_Counter++;
        MostUsedCounter::instance()->add(d->m_GconfKeyUsage);

}
bool DcpAppletMetadata::orderLessThan(DcpAppletMetadata *meta1,
                                      DcpAppletMetadata *meta2)
{
    return meta1->order() < meta2->order();
}

bool DcpAppletMetadata::usageGreatherThan(DcpAppletMetadata *meta1,
                                          DcpAppletMetadata *meta2)
{
    return meta1->usage() > meta2->usage();
}
