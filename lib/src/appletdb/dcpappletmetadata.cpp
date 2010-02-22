/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include <DuiLocale>

#include "dcpappletmetadata.h"
#include "dcpappletmetadata_p.h"
#include "dcpapplet.h"
#include "dcpwidgettypes.h"
#include "dcpappletdb.h"
#include "dcpappletloader.h"
#include "dcpbrief.h"
#include "dcpappletif.h"
#include "dcpwidget.h"
#include "dcpmostusedcounter.h"

#define DEBUG
#include "dcpdebug.h"



DcpAppletMetadataPrivate::DcpAppletMetadataPrivate ()
    : m_AppletLoader (0),
      m_Brief (0),
      m_DesktopEntry (0),
      m_Parent (0),
      m_Disabled (false)
{
}

DcpAppletMetadataPrivate::~DcpAppletMetadataPrivate ()
{
    if (m_AppletLoader)
        m_AppletLoader->deleteLater ();

    if (m_Brief) 
        m_Brief->deleteLater ();

    if (m_DesktopEntry) 
        delete m_DesktopEntry;
}


DcpAppletMetadata::DcpAppletMetadata (
        const QString& filename)
: d_ptr (new DcpAppletMetadataPrivate)
{
    DCP_DEBUG ("*** filename = '%s'", DCP_STR(filename));

    d_ptr->m_FileName = filename;
    d_ptr->m_DesktopEntry = new DuiDesktopEntry(filename);
    d_ptr->m_LastModified = QFileInfo(filename).lastModified().time();
}

DcpAppletMetadata::~DcpAppletMetadata ()
{
    DCP_DEBUG ("Destroying %p", this);
    delete d_ptr;
}

// TODO XXX rename
bool
DcpAppletMetadata::isValid () const
{
    if (binary().isEmpty() &&
            dslFilename().isEmpty()) {
        /*
         * FIXME: Maybe we should return false then?
         */
        DCP_WARNING ("The applet binary and the shell command also empty.");
    }

    DCP_DEBUG ("Returning %s for '%s'", 
            desktopEntry()->isValid() ? "true" : "false",
            DCP_STR (binary()));

    return desktopEntry()->isValid();
}

// TODO XXX rename
bool 
DcpAppletMetadata::isModified() const
{
    QTime lastModified = QFileInfo(d_ptr->m_FileName).lastModified().time();
    bool modified = lastModified !=  d_ptr->m_LastModified;
    return modified;
}

/*!
 * Returns the value of the "DCP/Category" key from the desktop file.
 */
QString 
DcpAppletMetadata::category () const
{
    return desktopEntryStr (KeyCategory);
}

/*!
 * Returns the value of the "DUI/X-DUIApplet-Applet" key from the desktop file.
 * This is the binary applet file name, a file name of the shared object
 * containing the binary code of the applet.
 */
QString 
DcpAppletMetadata::binary () const
{
    return desktopEntryStr (KeyBinary);
}

QString 
DcpAppletMetadata::dslFilename () const
{
    return desktopEntryStr (KeyDslFilename);
}

/*!
 * Returns the value of the "DUI/X-DUIApplet-ApplicationCommand" key from the
 * desktop file. This is the application command that will be executed when the
 * applet is activated.
 */
QString 
DcpAppletMetadata::applicationCommand () const
{
    return desktopEntryStr (KeyApplicationCommand);
}

/*!
 * Returns true if the metadata has a shell command associated to it.
 */
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
    QString filename = binary ();

    if (filename.isEmpty())
        return filename;

    return APPLET_LIBS "/" + filename;
}

QString 
DcpAppletMetadata::parentName () const
{
    return desktopEntryStr (KeyParent);
}

/*!
 * \brief Returns what type of brief widget shall an applet variant use.
 *
 * Gets the required brief widget type code of the applet variant. 
 */
int 
DcpAppletMetadata::widgetTypeID () const
{
    int         retval;
    DcpBrief   *brief = getBrief ();

    /*
     * If we have a brief and it provides us a widget type id that is valid, we
     * can use that.
     */
    if (brief != NULL) {
        retval = brief->widgetTypeID ();
        if (DcpWidgetType::isIdValid(retval)) {
            DCP_DEBUG ("brief->widgetTypeID () provides a widget type.");
            return retval;
        } else {
            /* FIXME: for supporting old api,
             * please remove ones deprecated ids are removed */
            switch (retval) {
                case DCPLABELBUTTON:
                case DCPLABEL2BUTTON:
                case DCPLABEL2TOGGLE:
                    return DcpWidgetType::Toggle;
                case DCPLABEL2IMAGE:
                    return DcpWidgetType::Image;
                case DCPLABEL:
                case DCPLABEL2:
                    return DcpWidgetType::Label;
            };
        }
    }

    /*
     * Otherwise we check the "DCP/WidgetType" key in the desktop file. If it is
     * valid we return that as a numerical value.
     */
    QString typeName = desktopEntryStr (KeyWidgetType);
    if (!typeName.isEmpty()) {
        for (retval = DcpWidgetType::BriefInvalid; retval < DcpWidgetType::IdMax; retval++) {
            if (DcpWidgetType::names[retval - DcpWidgetType::BriefInvalid] == typeName && 
                    DcpWidgetType::isIdValid (retval)) {
                DCP_DEBUG ("Desktop file provides a widget type: '%s'",
                        DCP_STR (typeName));
                return retval;
            }
        }
    }

    /*
     * Otherwise we return the default value, simple plugins can rely on this.
     */
    DCP_DEBUG ("Using default widget type.");
    return DcpWidgetType::Label;
}

Qt::Alignment 
DcpAppletMetadata::align () const
{
    if (getBrief()){
        return getBrief()->align();
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

DcpAppletMetadata *
DcpAppletMetadata::parent () const
{
    return d_ptr->m_Parent;
}

bool 
DcpAppletMetadata::toggle () const
{
    if (getBrief()) {
        return getBrief()->toggle ();
    }

    qWarning() << Q_FUNC_INFO << "no brief"; 
    return false;
}


/*! @brief The name of the catalog file which contains the applet's translation
 *
 *  @returns For example duicontrolpanel-languageapplet if the translations are
 *  in the following files: duicontrolpanel-languageapplet_en_GB.qm ...
 */
QString
DcpAppletMetadata::translationCatalog() const
{
    return desktopEntryStr(KeyNameCatalog);
}


QString
DcpAppletMetadata::text1 () const
{
    QString id = desktopEntryStr(KeyNameId);
    QString name = desktopEntryStr(KeyName);
    if (qtTrId(qPrintable(id)) == id)
        return ("!! " + name);
    else
        return qtTrId(qPrintable(id));
}

QString 
DcpAppletMetadata::text2 () const
{
    /*
     * FIXME: This feature is not in the UI spec, we have no localization for
     * the string.
     */
    if (isDisabled())
        return QString ("Disabled");
    /*
     * This way if we have a brief we can not specify the second line in the
     * desktop file.
     */
    if (getBrief())
        return getBrief()->valueText();

    // static way
    return desktopEntryStr(KeyText2);
}

/*!
 * FIXME: The name of this function is easy to misunderstand. It does not return
 * an image, and it is not clear if the string is a name or a filename.
 *
 * Found in dcpbriefwidget.cpp, this is an image name. It should be renamed as
 * such.
 */
QString 
DcpAppletMetadata::image () const
{
    if (getBrief())
        return getBrief()->image();

    // static way
    return desktopEntryStr(KeyImage);
}

QString 
DcpAppletMetadata::toggleIconId () const
{
    if (getBrief())
        return getBrief()->toggleIconId();

    // static way
    return desktopEntryStr(KeyToggleIconId);
}

/*!
 * \returns The status text/error message of the applet variant.
 */
QString 
DcpAppletMetadata::errorMsg () const 
{
    QString retval;

    if (!isValid())
        retval = "The desktop file is invalid.";
    else if (applet() != NULL)
        retval = "OK";
    else 
        retval = d_ptr->m_AppletLoader->errorMsg();

    return retval;
}


/*!
 * \brief A slot for the inter plugin activation.
 * \param appletName The name of the applet to activate.
 * 
 * \details This slot will activate an other applet. First the function will
 * find the applet using the applet database then it will emit a signal for it,
 * so it is going to be started.
 */
bool 
DcpAppletMetadata::activatePluginByName (
        const QString &appletName) const
{
    DcpAppletMetadata  *otherApplet;
    DcpWidget          *senderWidget = qobject_cast<DcpWidget *> (sender());

    Q_ASSERT (senderWidget != NULL);
   
    DCP_WARNING ("Want to start '%s' by %s/%d", 
            DCP_STR (appletName),
            DCP_STR (name()),
            senderWidget->getWidgetId());

    otherApplet = DcpAppletDb::instance()->applet (appletName);
    if (otherApplet) {
        DCP_DEBUG ("Emitting %p->activateWithReferer (%s, %d)", 
                otherApplet,
                DCP_STR (name()), 
                senderWidget->getWidgetId());
        emit otherApplet->activateWithReferer (
                name(), senderWidget->getWidgetId());

        return true;
    }
        
    DCP_WARNING ("Applet with name '%s' not found.", DCP_STR (appletName));
    return false;
}

void 
DcpAppletMetadata::setToggle (
        bool checked)
{
    if (getBrief()) {
        getBrief()->setToggle (checked);
    } else {
        qWarning("Can not set toggle state for the applet %s",
                 qPrintable(d_ptr->m_FileName));
    }
}

bool 
DcpAppletMetadata::isUnique () const
{
    DCP_DEBUG ("Returning %s for %s",
            !desktopEntryStr(KeyUnique).isEmpty() ? "true" : "false",
            DCP_STR (binary()));

    return !desktopEntryStr(KeyUnique).isEmpty();
}

QString 
DcpAppletMetadata::part () const
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
    if (!applet())
        return -1;

    return applet()->partID (part());
}

int 
DcpAppletMetadata::usage () const
{
    return MostUsedCounter::instance()->getUsageCount (
            QFileInfo(fileName()).baseName()
    );
}

int 
DcpAppletMetadata::order () const
{
    return desktopEntry()->value(Keys[KeyOrder]).toInt();
}

DcpAppletIf *
DcpAppletMetadata::applet () const
{
    DCP_DEBUG ("");

    if (d_ptr->m_Parent)
        return d_ptr->m_Parent->applet();

    if (d_ptr->m_AppletLoader == 0) {
        d_ptr->m_AppletLoader = new DcpAppletLoader (this);
    }

    /*
     * FIXME: This way we try to load the applet binary every time this function
     * is called. We should remember we failed instead.
     */
    return d_ptr->m_AppletLoader->applet();
}

DuiDesktopEntry *
DcpAppletMetadata::desktopEntry () const
{
    return d_ptr->m_DesktopEntry;
}

DcpBrief *
DcpAppletMetadata::getBrief () const
{
    if (d_ptr->m_Brief == 0 && applet() != 0) {
        d_ptr->m_Brief = applet()->constructBrief (getMainWidgetId());

        if (d_ptr->m_Brief != 0)
            connect (d_ptr->m_Brief, SIGNAL (valuesChanged ()), 
                    this, SIGNAL (briefChanged ()));
            connect (d_ptr->m_Brief, SIGNAL (activateSignal ()), 
                    this, SLOT (activateSlot ()));
    }

    return d_ptr->m_Brief;
}

void 
DcpAppletMetadata::activateSlot ()
{
    DCP_DEBUG ("Emitting activate()");
    emit activate();
}

// TODO XXX rename
QString 
DcpAppletMetadata::name () const
{
    return desktopEntry()->name().trimmed();
}

// TODO XXX rename
QString 
DcpAppletMetadata::fileName () const
{
    return desktopEntry()->fileName();
}

QString 
DcpAppletMetadata::desktopEntryStr (
        int id) const
{
    return desktopEntry()->value(Keys[id]).trimmed();
}

void 
DcpAppletMetadata::cleanup ()
{
    if (d_ptr->m_AppletLoader)
        d_ptr->m_AppletLoader->deleteLater();
    d_ptr->m_AppletLoader = 0;
}

void 
DcpAppletMetadata::setParent (
        DcpAppletMetadata *parent)
{
    d_ptr->m_Parent = parent;
}

/*!
 * This slot will 1) count the activations for the 'most used' category 2)
 * re-enable if the applet is disabled and 3) send the activate() signal so
 * thath the applet will be loaded and shown.
 */
void 
DcpAppletMetadata::slotClicked ()
{
    MostUsedCounter::instance()->incrementUsageCount (
            QFileInfo(fileName()).baseName()
    );

    if (isDisabled()) {
        DCP_DEBUG ("Enabling debug.");
        setDisabled (false);
    }

    emit activate ();
}

bool 
DcpAppletMetadata::orderLessThan (
        DcpAppletMetadata *meta1,
        DcpAppletMetadata *meta2)
{
    return meta1->order () < meta2->order ();
}

bool 
DcpAppletMetadata::usageGreatherThan (
        DcpAppletMetadata *meta1,
        DcpAppletMetadata *meta2)
{
    return meta1->usage() > meta2->usage();
}

bool
DcpAppletMetadata::isDisabled () const
{
    DCP_DEBUG ("*** %s is %s", 
            DCP_STR (name()),
            d_ptr->m_Disabled ? "disabled" : "enabled");
    return d_ptr->m_Disabled; 
}

void
DcpAppletMetadata::setDisabled (
        bool disabled)
{
    DCP_DEBUG ("*** setting %s to %s", 
            DCP_STR (name()),
            disabled ? "disabled" : "enabled");
    d_ptr->m_Disabled = disabled;
}

