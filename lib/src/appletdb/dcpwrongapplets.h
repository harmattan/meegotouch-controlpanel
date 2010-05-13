/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPWRONGAPPLETS_H
#define DCPWRONGAPPLETS_H

#include <QSet>
#include <QHash>
#include <QString>
#include <QObject>

class DcpAppletMetadata;

/** class is internal, handles wrong applet markings and queries */
/*
 * To disable the applet segfault protection please check the 
 * DcpWrongApplets::sm_Disabled in the dcpwrongapplets.cpp file.
 */
class DcpWrongApplets: 
    public QObject
{
Q_OBJECT

public:
    static DcpWrongApplets* instance ();
    static void destroyInstance();
    static void disable();
    static bool isDisabled() { return sm_Disabled; }

    void markAsMaybeBad (
            const QString &badSoPath,
            const char    *caller);

    void unmarkAsMaybeBad (
            const QString &badSoPath,
            const char    *caller);

    static bool 
        isAppletRecentlyCrashed (
            const QString           &badSoPath);

    static bool isAppletRecentlyCrashed (
            const DcpAppletMetadata *metadata);

    const QSet<QString> &badApplets () const;
    static QSet <QString> 
        queryBadApplets ();

private:
    DcpWrongApplets();
    ~DcpWrongApplets();
    // not a public header so private data members are allowed here
    static DcpWrongApplets *sm_Instance;
    void removeBadsOnDcpTimeStampChange();

    // some speed up caches to avoid unnecessery gconf access
    QSet<QString> m_BadApplets;
    static bool sm_Disabled;

    friend class Ut_DcpWrongApplets;
};


#endif

