#include "exampletimeplugin.h"

#include <QDeclarativeExtensionPlugin>
#include <qdeclarative.h>
#include <QTime>
#include <QTimer>

TimeModel::TimeModel(QObject *parent) : QObject(parent)
{
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SIGNAL(timeChanged()));

    // timer will fire in every sec:
    timer->start(1000);
}

QString TimeModel::text() const
{
    return QTime::currentTime().toString();
}


void ExampleTimePlugin::registerTypes(const char *uri)
{
    qmlRegisterType<TimeModel>(uri, 1, 0, "Time");
}

Q_EXPORT_PLUGIN2(qmlqtimeexampleplugin, ExampleTimePlugin);

