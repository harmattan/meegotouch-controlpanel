#ifndef QPLUGINLOADER_FAKE_H__
#define QPLUGINLOADER_FAKE_H__

#include <QtDebug>
#include "dcpappletloader-applet.h"

static bool qPluginLoaderFakeSuccessful = true;
static const QString fakeErrorMsg("fake-error-msg");


QPluginLoader::QPluginLoader(const QString &fileName, QObject *parent)
{
    Q_UNUSED(fileName);
    Q_UNUSED(parent);
}

QPluginLoader::~QPluginLoader() {}

bool QPluginLoader::load()
{
    return qPluginLoaderFakeSuccessful;
}

QString QPluginLoader::errorString() const
{
    if (qPluginLoaderFakeSuccessful) {
        return "";
    }

    return fakeErrorMsg;
}

QObject *QPluginLoader::instance()
{
    if (qPluginLoaderFakeSuccessful) {
        return new DcpAppletLoaderApplet();
    }

    return 0;
}

#endif
