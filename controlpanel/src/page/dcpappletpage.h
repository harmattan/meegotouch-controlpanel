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

    virtual void refreshContent ();
    virtual void createContent ();

    void setApplet(DcpAppletObject *applet, int widgetId = -1);
    virtual void reload ();
    bool hasWidget ();
    bool hasError ();

protected:
    virtual void retranslateUi ();
    void replaceActions(const QVector<DuiAction*>& actions);

protected slots:
    virtual void back ();

private:
    void changeWidget (int widgetId);
    void dropWidget ();
    void dropMissingLabel ();
    void loadMainWidget ();

    DcpAppletObject   *m_Applet;
    int m_WidgetId;
    bool                 m_ReloadNeeded;
    DcpWidget           *m_MainWidget;
    DuiLabel            *m_MissingLabel;
    QVector<DuiAction*> m_Actions;
};

#endif

