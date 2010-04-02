/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPAPPLETDB_FAKE_H
#define DCPAPPLETDB_FAKE_H

#include "dcpappletdb.h"
#include "dcpappletdb_p.h"
#include "dcpappletmetadata.h"
#include "dcpappletobject.h"

DcpAppletDb::DcpAppletDb (
        const QString   &pathName,
        const QString   &nameFilter) : d_ptr(new DcpAppletDbPrivate())
{
    Q_UNUSED(pathName);
    Q_UNUSED(nameFilter);
}

DcpAppletDb *
DcpAppletDb::instance (
        const QString   &pathName,
        const QString   &nameFilter)
{
    if (!DcpAppletDbPrivate::sm_Instance) {
        DcpAppletDbPrivate::sm_Instance = new DcpAppletDb (
                pathName, nameFilter);
    }

    return DcpAppletDbPrivate::sm_Instance;
}

bool
DcpAppletDb::addFile(const QString& filename)
{
    Q_UNUSED(filename);
    return true;
}

bool
DcpAppletDb::addPath(const QString &pathName)
{
    Q_UNUSED(pathName);
    return true;
}

bool
DcpAppletDb::addFiles (
        const QString  &pathName, 
        const QString  &filter)
{
    Q_UNUSED(pathName);
    Q_UNUSED(filter);
    return true;
}
DcpAppletMetadataList 
DcpAppletDb::listByCategory (
        const char **category,
        int          n_categories,
        checkCategory   checkFunction)
{
    Q_UNUSED(category);
    Q_UNUSED(n_categories);
    Q_UNUSED(checkFunction);
    QList<DcpAppletMetadata*> filtered;
    return filtered;
}

DcpAppletMetadataList 
DcpAppletDb::listMostUsed ()
{
   DcpAppletMetadataList mostUsed;
   return mostUsed;
}


DcpAppletObject *
DcpAppletDb::applet (
        const QString &name)
{
    DcpAppletMetadata metadata(name);
    return new DcpAppletObject(&metadata);
}

#endif // DCPAPPLETDB_FAKE_H
