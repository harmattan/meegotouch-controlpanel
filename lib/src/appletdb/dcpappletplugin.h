/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 sts=4: */
#ifndef DCPAPPLETPLUGIN_H
#define DCPAPPLETPLUGIN_H

#include <QObject>
#include <QString>
class DcpAppletMetadata;
class DcpAppletIf;
class DcpAppletPluginPrivate;

class DcpAppletPlugin : public QObject
{
    Q_OBJECT

public:
    explicit DcpAppletPlugin(DcpAppletMetadata *metadata);
    virtual ~DcpAppletPlugin();

    DcpAppletIf *applet() const;
    bool isAppletLoaded() const;
    DcpAppletMetadata *metadata() const;
    const QString errorMsg () const;

protected:
    virtual void load ();
    virtual bool loadPluginFile (const QString &binaryPath);
    virtual bool loadDslFile    (const QString &dslPath);

private:
    DcpAppletPluginPrivate *const d_ptr;
    Q_DISABLE_COPY(DcpAppletPlugin);
};

#endif
