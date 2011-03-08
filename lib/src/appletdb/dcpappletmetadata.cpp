/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpappletmetadata.h"
#include "dcpappletmetadata_p.h"
#include "dcpapplet.h"
#include "dcpmostusedcounter.h"
#include "dcpwidgettypes.h"

#include "dcpdebug.h"

#include <MGConfItem>
#include <MLocale>
#include <mcollator.h>
#ifndef MEEGO
#include <sysinfo.h>
#endif

DcpAppletMetadata* DcpAppletMetadataPrivate::sm_LastUsed = 0;
QString DcpAppletMetadataPrivate::sm_SOPath = APPLET_LIBS "/";

static const QString lastUsedAppletKey = QString(MOSTUSEDCOUNTER_GCONFKEY) +
                                         "/lastUsed";

DcpAppletMetadataPrivate::DcpAppletMetadataPrivate ()
    :
      m_DesktopEntry (0),
      m_Disabled (false),
      m_Activated (0)
{
}

DcpAppletMetadataPrivate::~DcpAppletMetadataPrivate ()
{
    if (m_DesktopEntry) 
        delete m_DesktopEntry;
}


bool DcpAppletMetadataPrivate::caWarningIfNotMatch (
        int key, const QString &expected1, const QString &expected2)
{
    QString value = m_DesktopEntry->value(Keys[key]);

    if (expected1 == value) {
        // it has good value
        return true;
    }

    if (!expected2.isNull() && expected2 == value+"") {
        // it has good value
        return true;
    }

    // it has bad value:
    qWarning ("The .desktop file of \"%s\" applet is not prepared to "
              "be used as an action, because of key \"%s\" "
              "(should be: \"%s\", but it is: \"%s\")",
              qPrintable (m_DesktopEntry->name()),
              qPrintable (Keys[key]),
              qPrintable (expected2.isNull() ? expected1 :
                          expected2 + "\" or \""+ expected1),
              qPrintable (value));
    return false;
}


DcpAppletMetadata::DcpAppletMetadata (
        const QString& filename)
: d_ptr (new DcpAppletMetadataPrivate)
{
    DCP_DEBUG ("*** filename = '%s'", DCP_STR(filename));

    d_ptr->m_FileName = filename;
    d_ptr->m_DesktopEntry = new MDesktopEntry(filename);
    d_ptr->m_LastModified = QFileInfo(filename).lastModified().time();

    /* These warnings ensures that applet developers notices when the
     * .desktop file of their applet is not prepared for used as an
     * action (see libcontentaction-doc)
     *
     * To avoid zillions of warnings, we stop at the first one
     */
    if (!hasApplicationCommand()) {
        QString name = this->name();
        d_ptr->caWarningIfNotMatch (KeyService, "com.nokia.DuiControlPanel") &&
        d_ptr->caWarningIfNotMatch (KeyMethod,
                "com.nokia.DuiControlPanelIf.appletPage") &&
        d_ptr->caWarningIfNotMatch (KeyObjectPath, "/", "") &&
        d_ptr->caWarningIfNotMatch (KeyFixedArgs, name, name+";");
    } else {
        d_ptr->caWarningIfNotMatch (KeyExec, applicationCommand());
    }
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
 * Returns the value of the "M/X-MApplet-Applet" key from the desktop file.
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
 * Returns the value of the "M/X-MApplet-ApplicationCommand" key from the
 * desktop file. This is the application command that will be executed when the
 * applet is activated.
 */
QString 
DcpAppletMetadata::applicationCommand () const
{
    QString command = desktopEntryStr(KeyExec);
    return command.isEmpty() ? desktopEntryStr (KeyApplicationCommand)
        : command;
}

/*!
 * Returns true if the metadata has a shell command associated to it.
 */
bool
DcpAppletMetadata::hasApplicationCommand () const
{
    return !applicationCommand().isEmpty();
}

/*
 * Returns the full path of the applet plugin filename, that is the name of the
 * shared object, that contains the applet binary program or if the 
 * "X-MApplet-Applet" field of the desktop file is empty returns the empty
 * string.
 */
QString
DcpAppletMetadata::fullBinary () const
{
    QString filename = binary ();

    if (filename.isEmpty())
        return filename;

    return DcpAppletMetadataPrivate::sm_SOPath + filename;
}

QString DcpAppletMetadata::defaultSOPath () {
    return DcpAppletMetadataPrivate::sm_SOPath;
}

void DcpAppletMetadata::setDefaultSOPath (const QString& path) {
    DcpAppletMetadataPrivate::sm_SOPath = path;
    // ensure it ends with "/" :
    if (!path.endsWith ("/")) DcpAppletMetadataPrivate::sm_SOPath += "/";
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
        DCP_WARNING ("Unknown widget type '%s' in desktop file '%s'",
                     qPrintable(typeName), qPrintable(fileName()));
    }

    /*
     * Otherwise we return the default value, simple plugins can rely on this.
     */
    DCP_DEBUG ("Using default widget type.");
    return DcpWidgetType::Label;
}

Qt::Orientation
DcpAppletMetadata::textOrientation () const
{
    QString ori = desktopEntryStr(KeyTextOrientation).toUpper();
    if (ori == "HORIZONTAL")
        return Qt::Horizontal;

    return Qt::Vertical;
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

bool 
DcpAppletMetadata::toggle () const
{
    return false;
}


/*! @brief The list of catalog names the applets needs
 *
 *  @returns The list of catalog names which contains the applet's translations.
 */
QStringList
DcpAppletMetadata::translationCatalogs() const
{
    // the catalogs are splitted with comma
    // (and maybe some whitespace follows it)
    return desktopEntryStr(KeyNameCatalog).split(QRegExp(",\\s*"));
}


QString
DcpAppletMetadata::text1 () const
{
    QString id = desktopEntryStr(KeyNameId);
    if (qtTrId(qPrintable(id)) == id) {
        QString name = desktopEntryStr(KeyName);
        return "!! " + name;
    } else {
        return qtTrId(qPrintable(id));
    }
}

QString
DcpAppletMetadata::text2 () const
{
    if (isDisabled()) {
        return QString ("Disabled");
    }

    QString id = desktopEntryStr(KeyText2Id);
    if (id.isEmpty() || qtTrId(qPrintable(id)) == id) {
        QString text = desktopEntryStr(KeyText2);
        if (text.isEmpty()) {
            // no text 2
            return text;
        } else {
            // no translation for text 2
            return "!! " + text;
        }
    } else {
        return qtTrId(qPrintable(id));
    }
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

#ifdef MOSTUSED
int 
DcpAppletMetadata::usage () const
{
    if (widgetTypeID() == DcpWidgetType::Button)
        return 0;
    
    return MostUsedCounter::instance()->getUsageCount (
       QFileInfo(fileName()).baseName()
    );
}

void
DcpAppletMetadata::incrementUsage()
{ 
    if (widgetTypeID() == DcpWidgetType::Button)
        return;
    MostUsedCounter::instance()->incrementUsageCount (
            QFileInfo(fileName()).baseName()
    );
    setLastUsed (this);
}
#endif

MDesktopEntry *
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


bool 
DcpAppletMetadata::orderLessThan (
        DcpAppletMetadata *meta1,
        DcpAppletMetadata *meta2)
{
    return meta1->order () < meta2->order ();
}

bool 
DcpAppletMetadata::nameLessThan (
        DcpAppletMetadata *meta1,
        DcpAppletMetadata *meta2)
{
    return MCollator::compare (meta1->name (), meta2->name ())
            == MLocale::LessThan;
}

bool 
DcpAppletMetadata::titleLessThan (
        DcpAppletMetadata *meta1,
        DcpAppletMetadata *meta2)
{
    return MCollator::compare (meta1->text1 (), meta2->text1 ())
            == MLocale::LessThan;
}

#ifdef MOSTUSED
bool 
DcpAppletMetadata::usageGreatherThan (
        DcpAppletMetadata *meta1,
        DcpAppletMetadata *meta2)
{
    return meta1->usage() > meta2->usage();
}
#endif

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


/*! \brief Marks the plugin as active
 *
 * We mean by active that the plugin is somehow displayed on the screen,
 * used by some widget etc. Think of this as a reference counter,
 * when the plugin is referred by anyone, its translation will be loaded
 * etc.
 */
void
DcpAppletMetadata::markActive()
{
    d_ptr->m_Activated++;
}

/*! \brief Marks the plugin inactive
 *
 * See markActive().
 */
void
DcpAppletMetadata::markInactive()
{
    int& count = d_ptr->m_Activated;
    if (count > 0) {
        count --;
    } else {
        DCP_WARNING("Internal error: plugin was inactivated "
                    "more times then activated (%s)", qPrintable(name()));
    }
}

/*! \brief Returns if the plugin is active or not
 *
 * See markActive().
 */
bool
DcpAppletMetadata::isActive() const
{
    return d_ptr->m_Activated;
}

/*! \brief Returns the last openned applet's metadata
 */
DcpAppletMetadata* DcpAppletMetadata::lastUsed ()
{
    return DcpAppletMetadataPrivate::sm_LastUsed;
}

void DcpAppletMetadata::setLastUsed (DcpAppletMetadata* metadata)
{
    DcpAppletMetadataPrivate::sm_LastUsed = metadata;

    // store the last used applet:
    DcpAppletMetadata* lastUsed = DcpAppletMetadata::lastUsed();
    if (lastUsed) {
        MGConfItem(lastUsedAppletKey).set (lastUsed->fileName());
    }
}

/*!
 * \brief Queries the path of the desktop file of the last used metadata
 */
QString DcpAppletMetadata::storedLastUsedItem ()
{
    return MGConfItem(lastUsedAppletKey).value ().toString ();
}

/*!
 * \brief Quieries the help id of the applet.
 */
QString DcpAppletMetadata::helpId() const
{
    return desktopEntryStr(KeyHelpId);
}

/* Returns the product version string */
inline const QString& product()
{
    static QString result;
#ifdef MEEGO
    return result;
#else
    if (result.isNull()) {
        struct system_config *sc = 0;
        if( sysinfo_init(&sc) == 0 ) {
            uint8_t *data = 0;
            unsigned long size = 0;
            if( sysinfo_get_value(sc, "/component/product", &data, &size) == 0 ) {
                result = QString::fromLatin1 ((const char*)data, size);
                free(data);
            }
        }
        sysinfo_finish(sc);

        // this prevents that this block runs twice:
        if (result.isNull()) result = "";

        qDebug ("Product is \"%s\"", qPrintable(result));
    }
    return result;
#endif
}

bool DcpAppletMetadata::isHidden() const
{
    QString doNotShowOn = desktopEntryStr (KeyDoNotShowOn);
    QString onlyShowOn = desktopEntryStr (KeyOnlyShowOn);
    const QString& productStr = product();

    // under scratchbox or on unknown product we do not hide:
    if (productStr.isEmpty()) return false;

    // we hide if onlyShowOn list does not contain the product
    if (!onlyShowOn.isEmpty()) {
        return !onlyShowOn.split(",").contains (productStr);
    }

    // match do not show on:
    if (!doNotShowOn.isEmpty()) {
        if (doNotShowOn.split(",").contains (productStr)) {
            return true;
        }
    }

    // the default is visible:
    return false;
}

bool DcpAppletMetadata::hasMainView () const
{
    QString has = desktopEntryStr(KeyHasMainView);
    if (has == "1") return true;
    if (has == "0") return false;
    if (!has.isEmpty()) {
        qWarning ("Unknown value for key %s in %s",
                  qPrintable (Keys[KeyHasMainView]),
                  qPrintable (fileName()));
    }
    // return default:
    int type = widgetTypeID();
    if (type == DcpWidgetType::Toggle || type == DcpWidgetType::Button ||
        type == DcpWidgetType::Slider)
    {
        return false;
    } else {
        return true;
    }
}

QString DcpAppletMetadata::sliderLeftImage () const
{
    return desktopEntryStr(KeySliderLeftImage);
}

QString DcpAppletMetadata::sliderRightImage () const
{
    return desktopEntryStr(KeySliderRightImage);
}

bool DcpAppletMetadata::hasInProcessBrief () const
{
    // of we have no library, we can be "inprocess" (who cares)
    if (binary().isEmpty()) {
        return true;
    }

    // if we are special type, we have no other choice:
    if (widgetTypeID() == DcpWidgetType::Special) {
        return true;
    }

    /*
     * If an applet wants to create dialog and
     * notification which requires it to be loaded, it can override
     * that it should not be handled out of process from its .desktop file.
     *
     * However, we could make an api for dialog requests
     * and then it would make this unecessery
     */
    return desktopEntryStr(KeyForceInProcessBrief) == "1";
}

