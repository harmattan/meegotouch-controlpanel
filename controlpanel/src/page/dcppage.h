#ifndef DCPPAGE_H
#define DCPPAGE_H

#include <DuiApplicationPage>
#include <Pages>

class QGraphicsLinearLayout;

/*
 * FIXME: This is a public hader, it should not contain inline functions and
 * class members that are suject to change.
 */
class DcpPage : public DuiApplicationPage
{
    Q_OBJECT

public:
    DcpPage();
    virtual ~DcpPage();
    virtual void createContent();
    virtual void connectSignals();
    virtual void disconnectSignals();

    Pages::Handle handle() const;
    virtual void setHandle (const Pages::Handle &handle);
    virtual void setHandle (Pages::Id id, const QString &param);

    Pages::Handle referer() const;
    void setReferer(const Pages::Handle &referer);
    virtual void setReferer(Pages::Id id, const QString &param="");
    
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
