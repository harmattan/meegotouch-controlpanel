#ifndef DCPREMOTEBRIEF_H
#define DCPREMOTEBRIEF_H

#include "dcpbrief.h"

class DcpRemoteBrief: public DcpBrief
{
    Q_OBJECT

public:
    DcpRemoteBrief(const QString& appletName, QObject* parent = 0);
    virtual ~DcpRemoteBrief();

    virtual int widgetTypeID() const;
    virtual QString valueText() const;
    virtual QString icon() const;
    virtual bool toggle() const;
    virtual QString titleText() const;
    virtual QString helpId() const;

    QString name () const;
    QString value (const char* id) const;
    void setValue (const char* id, const QString& value);
    void emitChange ();

public slots:
    virtual void setToggle(bool toggle);

private:
    class DcpRemoteBriefPriv* priv;
};


#endif // DCPREMOTEBRIEF_H

