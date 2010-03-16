/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include <DuiLocale>

#include "dcpappletmetadata.h"
#include "dcpappletmetadata_p.h"
#include "dcpapplet.h"
#include "dcpmostusedcounter.h"
#include "dcpwidgettypes.h"

//#define DEBUG
#include "dcpdebug.h"



DcpAppletMetadataPrivate::DcpAppletMetadataPrivate ()
    :
      m_DesktopEntry (0),
      m_Parent (0),
      m_Disabled (false)
{
}

DcpAppletMetadataPrivate::~DcpAppletMetadataPrivate ()
{
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

bool
DcpAppletMetadata::isValid () const
{
    if (binary().isEmpty() &&
            dslFilename().isEmpty() && !hasApplicationCommand()) {
        DCP_WARNING ("The applet binary and the shell command also empty.");
        return false;
    }

    DCP_DEBUG ("Returning %s for '%s'", 
            desktopEntry()->isValid() ? "true" : "false",
            DCP_STR (binary()));

    return desktopEntry()->isValid();
}

bool 
DcpAppletMetadata::isModified() const
{
    QTime lastModified = QFileInfo(d_ptr->m_FileName).lastModified().time();
    bool modified = lastModified !=  d_ptr->m_LastModified;

    DCP_DEBUG ("Returning %s for '%s'", 
            modified ? "true" : "false",
            DCP_STR (binary()));
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
    QString typeName = desktopEntryStr (KeyWidgetType);
    if (!typeName.isEmpty()) {
        for (int retval = DcpWidgetType::BriefInvalid; retval < DcpWidgetType::IdMax; retval++) {
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
    // static way
    return desktopEntryStr(KeyText2);
}

QString 
DcpAppletMetadata::imageName () const
{
    return desktopEntryStr(KeyImage);
}

QString 
DcpAppletMetadata::toggleIconId () const
{
    return desktopEntryStr(KeyToggleIconId);
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

int 
DcpAppletMetadata::order () const
{
    return desktopEntry()->value(Keys[KeyOrder]).toInt();
}

int 
DcpAppletMetadata::usage () const
{
    return MostUsedCounter::instance()->getUsageCount (
            QFileInfo(fileName()).baseName()
    );
}

void
DcpAppletMetadata::incrementUsage()
{ 
    MostUsedCounter::instance()->incrementUsageCount (

            QFileInfo(fileName()).baseName()
    );
}

DuiDesktopEntry *
DcpAppletMetadata::desktopEntry () const
{
    return d_ptr->m_DesktopEntry;
}


QString 
DcpAppletMetadata::name () const
{
    return desktopEntry()->name().trimmed();
}

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
DcpAppletMetadata::setParent (
        DcpAppletMetadata *parent)
{
    d_ptr->m_Parent = parent;
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

