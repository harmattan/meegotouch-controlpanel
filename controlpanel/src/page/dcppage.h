#ifndef DCPPAGE_H
#define DCPPAGE_H

#include <DuiApplicationPage>
#include <Pages>

class QGraphicsLinearLayout;

class DcpPage : public DuiApplicationPage
{
    Q_OBJECT

public:
    DcpPage();
    virtual ~DcpPage();
    virtual void createContent();
    virtual void connectSignals();
    virtual void disconnectSignals();
    Pages::Handle handle() const {return m_Handle;}
    virtual void setHandle(const Pages::Handle &handle) {m_Handle = handle;}
    virtual void setHandle(Pages::Id id, const QString &param="")
        {m_Handle.id = id; m_Handle.param = param;}
    Pages::Handle referer() const {return m_Referer;}

    void setReferer(const Pages::Handle &referer) {m_Referer = referer;}
    virtual void setReferer(Pages::Id id, const QString &param="")
        {m_Referer.id = id; m_Referer.param = param;}
    QGraphicsLinearLayout *mainLayout();

    virtual void reload();

public slots:
    virtual void back();
    virtual void organizeContent(const Dui::Orientation& ori);

signals:
    void openSubPage(Pages::Handle handle);

protected:
    void append (QGraphicsWidget* widget);
    void remove (QGraphicsWidget* widget);

private:
    void connectOrientation();
    Pages::Handle m_Handle;
    Pages::Handle m_Referer;
    void createLayout();
};

#endif // DCPPAGE_H
