#ifndef EXAMPLETIMEPLUGIN_H
#define EXAMPLETIMEPLUGIN_H

#include <QDeclarativeExtensionPlugin>

class TimeModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text NOTIFY timeChanged)

public:
    TimeModel (QObject* parent = 0);
    QString text() const;

signals:
    void timeChanged();
};

class ExampleTimePlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    void registerTypes(const char *uri);
};

#endif // EXAMPLETIMEPLUGIN_H


