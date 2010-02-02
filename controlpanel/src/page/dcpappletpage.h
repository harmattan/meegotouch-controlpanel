#ifndef DCPAPPLETPAGE_H
#define DCPAPPLETPAGE_H

#include <DcpPage>
#include <Pages>
#include <QVector>

class DcpWidget;
class DcpAppletMetadata;
class DuiLabel;
class DuiAction;

class DcpAppletPage : public DcpPage
{
Q_OBJECT

public:
    DcpAppletPage(DcpAppletMetadata *metadata);
    virtual ~DcpAppletPage();

    virtual void refreshContent ();
    virtual void createContent ();

    void setMetadata (DcpAppletMetadata *metadata);
    virtual void reload ();
    bool hasWidget ();
    bool hasError ();

protected:
    virtual void retranslateUi ();
    void replaceActions(const QVector<DuiAction*>& actions);

protected slots:
    void changeWidget (int widgetId);
    virtual void back ();

private:
    void dropWidget ();
    void dropMissingLabel ();
    void loadMainWidget ();

    DcpAppletMetadata   *m_Metadata;
    bool                 m_ReloadNeeded;
    DcpWidget           *m_MainWidget;
    DuiLabel            *m_MissingLabel;
    QVector<DuiAction*> m_Actions;
};

#endif

