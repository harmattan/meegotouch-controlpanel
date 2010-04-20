#ifndef STUB_GCONFITEMPRIVATE_H
#define STUB_GCONFITEMPRIVATE_H

#include <QString>
#include <QObject>

struct MGConfItemPrivate: public QObject
{
    Q_OBJECT
public:
    QString key;
    void emitChangedSignal() { emit valueChanged(); }
signals:
    void valueChanged();
};

#endif // STUB_GCONFITEMPRIVATE_H
