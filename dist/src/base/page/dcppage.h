#ifndef DCPPAGE_H
#define DCPPAGE_H

#include <DuiApplicationPage>
#include "pages.h"
class DuiPannableViewport;
class DcpBackgroundView;
class DuiLabel;
class DcpPage : public DuiApplicationPage
{
    Q_OBJECT
public:
    DcpPage();
    virtual void createContent();
    virtual void organizeContent(Dui::Orientation ori);
    Pages::Id pageId() const {return m_PageId;};
    void setPageId(Pages::Id pageId) {m_PageId = pageId;};
    Pages::Id referer() const {return m_Referer;};
    void setReferer(Pages::Id referer) {m_Referer = referer;};
    const QString title() const;
    virtual void setTitle(const QString& title);
    DuiPannableViewport* viewport() const {return m_DesktopViewport;};
signals:
    void openSubPage(Pages::Id subPageId);
protected:
   DuiPannableViewport *m_DesktopViewport;
   DcpBackgroundView *m_BackgroundView;
   DuiLabel *m_Title;
   Pages::Id m_PageId;
   Pages::Id m_Referer;
private:
};

#endif // DCPPAGE_H
