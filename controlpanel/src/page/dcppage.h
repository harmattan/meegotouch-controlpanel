#ifndef DCPPAGE_H
#define DCPPAGE_H

#include <DuiApplicationPage>
#include <Pages>

class QGraphicsLinearLayout;

/*
 * FIXME: This is a public hader, it should not contain inline functions and
 * class members that are subject to change.
 */
class DcpPage : public DuiApplicationPage
{
    Q_OBJECT

public:
    DcpPage();

    virtual void createContent();

    PageHandle handle () const;
    virtual void setHandle (const PageHandle &handle);
    virtual void setHandle (
                    PageHandle::PageTypeId id, 
                    const QString &param = "");

    PageHandle referer () const;
    virtual void setReferer (const PageHandle &referer);
    virtual void setReferer (
                    PageHandle::PageTypeId id, 
                    const QString &param = "");
    
    QGraphicsLinearLayout *mainLayout();

    virtual void reload();

public slots:
    virtual void back ();

signals:
    void openSubPage (PageHandle handle);
    void openSubPageWithReferer (const PageHandle &, const QString &, int);

protected:
    void appendWidget (QGraphicsWidget *widget);
    void removeWidget (QGraphicsWidget *widget);

private:
    void createLayout();

    PageHandle m_Handle;
    PageHandle m_Referer;
};

#endif
