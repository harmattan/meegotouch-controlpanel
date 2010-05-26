/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include "dcpappletmetadata.h"
#include "dcpappletmetadata_p.h"

/* Fake appletmetadata
 *
 * Works like a real one, but not using desktop files.
 * The returned values will be <filename>-<valuetype>, for example
 * the name will be "test-name" for an applet which was called with
 * "test" as filename in its constructor.
 */

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
}


DcpAppletMetadata::DcpAppletMetadata (const QString& filename)
: d_ptr (new DcpAppletMetadataPrivate)
{
    d_ptr->m_FileName = filename;
}

DcpAppletMetadata::~DcpAppletMetadata ()
{
    delete d_ptr;
}

bool
DcpAppletMetadata::isValid () const
{
    return true;
}

bool 
DcpAppletMetadata::isModified() const
{
    return false;
}

QString 
DcpAppletMetadata::category () const
{
    return d_ptr->m_FileName + "-category";
}

QString 
DcpAppletMetadata::binary () const
{
    return d_ptr->m_FileName + "-binary";
}

QString 
DcpAppletMetadata::dslFilename () const
{
    return d_ptr->m_FileName + "-dslFilename";
}

QString 
DcpAppletMetadata::applicationCommand () const
{
    return d_ptr->m_FileName + "-applicationCommand";
}

bool
DcpAppletMetadata::hasApplicationCommand () const
{
    return true;
}

QString
DcpAppletMetadata::fullBinary () const
{
    return d_ptr->m_FileName + "-fullBinary";
}

QString 
DcpAppletMetadata::parentName () const
{
    return d_ptr->m_FileName + "-parentName";
}

int 
DcpAppletMetadata::widgetTypeID () const
{
    return 0;
}

Qt::Alignment 
DcpAppletMetadata::align () const
{
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


QString
DcpAppletMetadata::translationCatalog() const
{
    return d_ptr->m_FileName + "-translationCatalog";
}


QString
DcpAppletMetadata::text1 () const
{
    return d_ptr->m_FileName + "-text1";
}

QString 
DcpAppletMetadata::text2 () const
{
    return d_ptr->m_FileName + "-text2";
}

QString 
DcpAppletMetadata::imageName () const
{
    return d_ptr->m_FileName + "-imageName";
}

QString 
DcpAppletMetadata::toggleIconId () const
{
    return d_ptr->m_FileName + "-toggleIconId";
}

bool 
DcpAppletMetadata::isUnique () const
{
    return false;
}

QString 
DcpAppletMetadata::part () const
{
    return QString();
}

int 
DcpAppletMetadata::order () const
{
    return 1;
}

int 
DcpAppletMetadata::usage () const
{
    return 1;
}

void
DcpAppletMetadata::incrementUsage()
{ 
}

MDesktopEntry *
DcpAppletMetadata::desktopEntry () const
{
    return 0;
}


QString 
DcpAppletMetadata::name () const
{
    return d_ptr->m_FileName + "-name";
}

QString 
DcpAppletMetadata::fileName () const
{
    return d_ptr->m_FileName;
}

QString 
DcpAppletMetadata::desktopEntryStr (int) const
{
    return QString();
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
    return d_ptr->m_Disabled;
}

void
DcpAppletMetadata::setDisabled ( bool val )
{
    d_ptr->m_Disabled = val;
}

void
DcpAppletMetadata::markActive()
{
    d_ptr->m_Activated++;
}

void
DcpAppletMetadata::markInactive()
{
    d_ptr->m_Activated--;
}

bool
DcpAppletMetadata::isActive() const
{
    return d_ptr->m_Activated;
}


