#ifndef DCPBRIEF_H
#define DCPBRIEF_H

#include <QObject>
#include <QString>

class DcpBrief: public QObject{
    Q_OBJECT
public:
    virtual ~DcpBrief();

    virtual int widgetTypeID() const;
    virtual QString valueText() const;
    virtual QString icon() const;

    virtual Qt::Alignment align() const;
    virtual bool toggle() const;
    virtual void setToggle (bool toggle);

    virtual QString image() const;

signals:
    // emitted when some of the values changed
    void valuesChanged();
};


#endif // DCPBRIEF_H
