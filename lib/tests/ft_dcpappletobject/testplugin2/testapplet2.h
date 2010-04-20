#ifndef TESTAPPLET2_H__
#define TESTAPPLET2_H__

#include <DcpAppletIf>
#include <QObject>

class DcpWidget;

class TestApplet2 : public QObject, public DcpAppletIf
{
    Q_OBJECT
    Q_INTERFACES(DcpAppletIf)

    public:

    virtual ~TestApplet2();

    virtual void init();
    virtual DcpWidget *constructWidget(int widgetId);
    virtual QString title() const;
    virtual QVector<MAction*> viewMenuItems();
    virtual DcpBrief *constructBrief(int);
};




#endif // TESTAPPLET2_H__
