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
/* vim:set et sw=4 ts=4 sts=4: */

#ifndef DCPAPPLETMETADATA_H
#define DCPAPPLETMETADATA_H

#include <QObject>
#include <QString>
#include <QStringList>

class MDesktopEntry;
class DcpAppletMetadataPrivate;


/*!
 * \brief This class contains all the information coming from the desktop file
 *        of the applet.
 *
 * \details This class provides all the information about an applet variant in
 *   practical format. Every applet can hold one or more .desktop file, for each
 *   there will be a #DcpAppletMetadata class object, and each will define a
 *   configuration for the applet binary. 
 *
 *   If an applet have more than one desktop file we say the applet have more
 *   than one applet variant, that is from the user point of view the applet
 *   seems like it were more than one applet, but these variants might share 
 *   common elements (UI, code and data).
 */
class DcpAppletMetadata : public QObject
{
    Q_OBJECT
public:
    DcpAppletMetadata (const QString& filename);
    virtual ~DcpAppletMetadata ();

    virtual bool isValid () const;
    virtual bool isUnique () const;
    virtual bool isModified () const;

    QString name () const;
    QString fileName () const;
    QString category () const;
    QString toggleIconId () const;
    int widgetTypeID() const;
    QString binary () const;
    QString dslFilename () const;
    QString applicationCommand () const;
    bool    hasApplicationCommand () const;
    bool toggle() const;
    QString fullBinary () const;

    Qt::Alignment align () const;

    QString text1 () const;
    QString text2 () const;
    QStringList translationCatalogs() const;

    QString imageName() const;

    int order () const;
    int usage () const;
    void incrementUsage();
    QString part () const;

    void setParent (DcpAppletMetadata *parent);
    DcpAppletMetadata* parent () const;
    QString parentName () const;

    static bool usageGreatherThan (
            DcpAppletMetadata *meta1,
            DcpAppletMetadata *meta2);

    static bool orderLessThan (
            DcpAppletMetadata *meta1,
            DcpAppletMetadata *meta2);

    static bool nameLessThan (
            DcpAppletMetadata *meta1,
            DcpAppletMetadata *meta2);

     bool isDisabled () const;
    void setDisabled (bool disabled);

    void markActive();
    void markInactive();
    bool isActive() const;

    /*! gets the last openned applet */
    static DcpAppletMetadata* lastUsed ();
    /*! sets the last openned applet */
    static void setLastUsed (DcpAppletMetadata* metadata);
    static QString storedLastUsedItem();

protected:
    MDesktopEntry* desktopEntry () const;
    QString desktopEntryStr (int id) const;
private:
    DcpAppletMetadataPrivate *const d_ptr;
    Q_DISABLE_COPY (DcpAppletMetadata);
    friend class Ut_DcpAppletMetadata;
};


#endif

