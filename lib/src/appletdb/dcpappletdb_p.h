/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPAPPLETDB_P_H
#define DCPAPPLETDB_P_H
#include <QMap>
#include <QString>

class DcpAppletDb;

typedef QMap<QString, DcpAppletMetadata*> DcpAppletMetadataMap;

//typedef bool (*checkCategory)(const QString &);

class DcpAppletDbPrivate
{
public:
    DcpAppletDbPrivate();
    ~DcpAppletDbPrivate();
    DcpAppletMetadataMap appletsByName;  
    DcpAppletMetadataMap appletsByFile; 
    QList<QString> paths;
    bool hasUniqueMetadata;
    static DcpAppletDb *sm_Instance;
};
#endif // DCPAPPLETDB_H

