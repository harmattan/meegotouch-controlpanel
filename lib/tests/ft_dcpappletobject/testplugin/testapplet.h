#ifndef TESTAPPLET_H__
#define TESTAPPLET_H__

#include <DcpAppletIf>
#include <QObject>

class DcpWidget;

class TestApplet : public QObject, public DcpAppletIf
{
    Q_OBJECT
    Q_INTERFACES(DcpAppletIf)

    public:

    virtual ~TestApplet();

    virtual void init();
    virtual DcpWidget *constructWidget(int widgetId);
    virtual QString title() const;
    virtual QVector<MAction*> viewMenuItems();
    virtual DcpBrief *constructBrief(int);
};




#endif // TESTAPPLET_H__
