#ifndef DCPREMOTEAPPLETOBJECT_H
#define DCPREMOTEAPPLETOBJECT_H

#include <DcpAppletObject>

class DcpRemoteAppletObject: public DcpAppletObject
{
    Q_OBJECT
public:
    DcpRemoteAppletObject(DcpAppletMetadata* metadata, QObject* parent = 0);

protected:
    virtual bool loadPluginFile (const QString &binaryPath);

private slots:
    void onActivated (int pageId);

private:
	
};


#endif // DCPREMOTEAPPLETOBJECT_H
