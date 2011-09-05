#include "dcpqmlcontacter.h"
#include "dcpqmlapplet.h"

DcpQmlContacter::DcpQmlContacter():
    QObject ()
{
}

DcpQmlContacter::~DcpQmlContacter()
{
}

void DcpQmlContacter::newPage (const QString& url)
{
    DcpQmlApplet::instance()->requestPage (url);
}

