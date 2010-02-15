/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 sts=4: */
#ifndef DCPAPPLETLOADER_H
#define DCPAPPLETLOADER_H

#include <QObject>
#include <QString>
class DcpAppletMetadata;
class DcpAppletIf;
class DcpAppletLoaderPrivate;

class DcpAppletLoader : public QObject
{
    Q_OBJECT

public:
    DcpAppletLoader (const DcpAppletMetadata *metadata);
    virtual ~DcpAppletLoader ();

    DcpAppletIf *applet();
    const DcpAppletMetadata *metadata() const;
    const QString errorMsg () const;

protected:
    virtual void load ();
    virtual bool loadPluginFile (const QString &binaryPath);
    virtual bool loadDslFile    (const QString &dslPath);

private:
    DcpAppletLoaderPrivate *const d_ptr;
    Q_DISABLE_COPY(DcpAppletLoader);
};

#endif
