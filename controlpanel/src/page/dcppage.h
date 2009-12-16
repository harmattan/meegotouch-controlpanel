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

    PageHandle handle() const;
    virtual void setHandle (const PageHandle &handle);
    virtual void setHandle (PageHandle::PageTypeId id, const QString &param="");

    PageHandle referer() const;
    void setReferer(const PageHandle &referer);
    virtual void setReferer(PageHandle::PageTypeId id, const QString &param="");
    
    QGraphicsLinearLayout *mainLayout();

    virtual void reload();

public slots:
    virtual void back();
    virtual void organizeContent(const Dui::Orientation& ori);

signals:
    void openSubPage (PageHandle handle);
    void openSubPageWithReferer (const PageHandle &, const QString &, int);

protected:
    void append (QGraphicsWidget* widget);
    void remove (QGraphicsWidget* widget);

private:
    void connectOrientation();
    PageHandle m_Handle;
    PageHandle m_Referer;
    void createLayout();
};

#endif // DCPPAGE_H
