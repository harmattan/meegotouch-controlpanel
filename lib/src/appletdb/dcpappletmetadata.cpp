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

DcpAppletMetadata* DcpAppletMetadataPrivate::sm_LastUsed = 0;

static const QString lastUsedAppletKey = QString(MOSTUSEDCOUNTER_GCONFKEY) +
                                         "/lastUsed";

DcpAppletMetadataPrivate::DcpAppletMetadataPrivate ()
    :
      m_DesktopEntry (0),
      m_Parent (0),
      m_Disabled (false),
      m_Activated (0)
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
    d_ptr->m_DesktopEntry = new MDesktopEntry(filename);
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
    return desktopEntryStr (KeyApplicationCommand);
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
        DCP_WARNING ("Unknown widget type '%s' in desktop file '%s'",
                     qPrintable(typeName), qPrintable(fileName()));
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
DcpAppletMetadata::nameLessThan (
        DcpAppletMetadata *meta1,
        DcpAppletMetadata *meta2)
{
    return MCollator::compare (meta1->name (), meta2->name ())
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


