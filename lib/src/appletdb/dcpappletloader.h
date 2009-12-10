/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 sts=4: */
#ifndef DCPAPPLETLOADER_H
#define DCPAPPLETLOADER_H

#include <QObject>
#include <QString>
class DcpAppletMetadata;
class DcpAppletIf;
class DcpAppletLoader : public QObject
{
    Q_OBJECT
public:
    DcpAppletLoader(const DcpAppletMetadata* metadata);
    virtual ~DcpAppletLoader();
    DcpAppletIf* applet() const {return m_Applet;};
    const DcpAppletMetadata* metadata() const {return m_Metadata;};
    const QString errorMsg() const {return m_ErrorMsg;};
protected:
    virtual void load ();
    virtual bool loadPluginFile (const QString &binaryPath);
    virtual bool loadDslFile    (const QString &dslPath);
private:
    const DcpAppletMetadata* m_Metadata;
    DcpAppletIf *m_Applet;
    QString m_ErrorMsg;
};

#endif // DCPAPPLETLOADER_H
