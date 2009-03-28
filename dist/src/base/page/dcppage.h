#ifndef DCPPAGE_H
#define DCPPAGE_H

#include <DuiApplicationPage>
#include "pages.h"
class DuiPannableViewport;
class DuiLabel;
class DuiLinearLayoutPolicy;

class DcpPage : public DuiApplicationPage
{
    Q_OBJECT

public:
    DcpPage();
    virtual ~DcpPage();
    virtual void createContent();
    virtual void organizeContent(Dui::Orientation ori);
    Pages::Handle handle() const {return m_Handle;};
    virtual void setHandle(Pages::Handle handle) {m_Handle = handle;}; 
    virtual void setHandle(Pages::Id id, const QString &param="") 
        {m_Handle.id = id; m_Handle.param = param;};
    Pages::Handle referer() const {return m_Referer;};
   
    void setReferer(Pages::Handle referer) {m_Referer = referer;}; 
    virtual void setReferer(Pages::Id id, const QString &param="") 
        {m_Referer.id = id; m_Referer.param = param;};
    const QString title() const;
    virtual void setTitle(const QString& title);
    DuiLinearLayoutPolicy *mainLayout() { return m_MainLayout; }

signals:
    void openSubPage(Pages::Handle handle);

protected slots:
    void onOrientationAngleChanged();

protected:
    void append (QGraphicsWidget* widget);

   QString m_Title;

   DuiLinearLayoutPolicy *m_MainLayout;

   Pages::Handle m_Handle;
   Pages::Handle m_Referer;
};

#endif // DCPPAGE_H
