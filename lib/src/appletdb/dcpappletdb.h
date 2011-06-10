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
#ifndef DCPAPPLETDB_H
#define DCPAPPLETDB_H

#include <QObject>
#include <QStringList>
#include <QMap>
#include "dcpapplet.h"

/*!
 * \class DcpAppletDb
 * \brief This singleton class keeps track of all installed applets of Conrol
 *   Panel
 *
 * \details Applet database can be filled with desktop files and then can
 *   be queried by category, usage, by applet name. 
 */
class DcpAppletMetadata;
class DcpAppletObject;

typedef QList<DcpAppletMetadata*> DcpAppletMetadataList;

typedef bool (*checkCategory)(const QString &);

class DcpAppletDbPrivate;
class DcpAppletDb: public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Gives back the db instance
     *
     * This function has two optional arguments, so the path and the filter can
     * be initialized as the very first step.
     * Pathname can also be a list of paths separated by ':'.
     */
    static DcpAppletDb *instance (
            const QString &pathName = DcpApplet::DefaultPath,
            const QString &nameFilter = "*.desktop");

    /*!
     * \brief Initializes an empty db.
     *
     * It can be used to avoid parsing the .desktop files on the instance
     * call. If db is already initialized, it just outputs a warning.
     */
    static void initEmptyDb ();

    /*! \brief adds files at a specified path pathName to the db */
    bool addPath (const QString &pathName);

    /* \brief adds files at specified pathName with specific name filter */
    bool addFiles (const QString &path, const QString &filter);

    /*! \brief Database destructor */
    virtual ~DcpAppletDb();

    /*! \brief List all applets
        \return the metadata list of the applets
     */
    DcpAppletMetadataList list() const;

    /*! \brief Queries the db for a specified applet category
        \param category the name of the category
        \return the metadata list of the matching applets
    */
    DcpAppletMetadataList listByCategory(
                    const QString &category);

    DcpAppletMetadataList listByCategory (
                    const char    **category,
                    int             n_categories,
                    checkCategory   checkFunction = 0);

    DcpAppletMetadataList listByCategory (
                    const QStringList& categories,
                    checkCategory   checkFunction = 0);

    /*! \brief List the four most used applets
        \details
        The first element will be the applet used last time,
        the next three will be the most frequently used ones.

        Returns an empty list in case nost used item handling
        is disabled.
     */
    DcpAppletMetadataList listMostUsed();

    /*! \return the object of an applet by name*/
    DcpAppletObject *applet(const QString& name);

    /*! \return the metadata of an applet by name*/
    DcpAppletMetadata *metadata(const QString& name);

    /*! \brief add one file to the db */
    bool addFile(const QString& filename);

    /*! \brief erase metadata from the db */
    void eraseEntry(DcpAppletMetadata *metadata);

    /*! \brief returns all applet names of the db */
    QStringList appletNames() const;

    /*! \brief checks if fileName has already added to the db */
    bool containsFile(const QString& fileName);

    /*! \brief checks if an applet with given name is already 
        in the db */
    bool containsName(const QString& name);

    /*! \brief checks if the applet with this name is loaded already
     */
    bool isAppletLoaded (const QString& name);

    /*! \brief Lists the loaded applets
     */
    QList<DcpAppletObject*> loadedApplets () const;

    /*! \brief destroys all the contents (metadata) of the db */
    void destroyData (void);
    static void destroy (void);

signals:
    void appletLoaded (DcpAppletObject *applet);

protected:
    /*! \brief protected constructor for singleton*/
    DcpAppletDb (const QString &pathName, const QString &nameFilter);
    /*! \brief Creates an empty db. */
    DcpAppletDb ();

private:
    DcpAppletDbPrivate *const d_ptr;
    Q_DISABLE_COPY(DcpAppletDb);
    friend class Ut_DcpAppletDb;
};

#endif // DCPAPPLETDB_H

