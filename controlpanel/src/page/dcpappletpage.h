#ifndef DCPAPPLETPAGE_H
#define DCPAPPLETPAGE_H

#include <DcpPage>
#include <Pages>
#include <QVector>

class DcpWidget;
class DcpAppletObject;
class DuiLabel;
class DuiAction;

class DcpAppletPage : public DcpPage
{
Q_OBJECT

public:
    DcpAppletPage(DcpAppletObject *applet, int widgetId = -1);
    virtual ~DcpAppletPage();

    virtual void createContent ();

    bool hasWidget ();
    bool hasError ();
    int widgetId ();
    DcpAppletObject* applet();

protected:
    virtual void retranslateUi ();

protected slots:
    virtual void back ();

private:
    void loadWidget (int widgetId);
    void load ();

    DcpAppletObject   *m_Applet;
    int m_WidgetId;
    DcpWidget           *m_MainWidget;
    DuiLabel            *m_MissingLabel;
};

#endif

