#ifndef DCPPAGE_H
#define DCPPAGE_H

#include <DuiApplicationPage>
#include "pages.h"
class DuiPannableViewport;
class DuiLabel;
class DuiLinearLayout;
class DcpPage : public DuiApplicationPage
{
    Q_OBJECT
public:
    DcpPage();
    virtual ~DcpPage();
    virtual void createContent();
    virtual void organizeContent(Dui::Orientation ori);
    Pages::Id pageId() const {return m_PageId;};
    void setPageId(Pages::Id pageId) {m_PageId = pageId;};
    Pages::Id referer() const {return m_Referer;};
    void setReferer(Pages::Id referer) {m_Referer = referer;};
    const QString title() const;
    virtual void setTitle(const QString& title);
    DuiPannableViewport* viewport() const {return m_DesktopViewport;};
    DuiWidget* panWidget() const {return m_PanWidget;};
    DuiLinearLayout* panLayout() const {return m_PanLayout;};
    void paint(QPainter *painter, 
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);
signals:
    void openSubPage(Pages::Id subPageId, const QString &param);
protected:
   DuiPannableViewport *m_DesktopViewport;
   DuiLabel *m_Title;
   DuiWidget *m_PanWidget;
   DuiLinearLayout *m_PanLayout;
   DuiLinearLayout *m_MainLayout;
   Pages::Id m_PageId;
   Pages::Id m_Referer;
private:
   const QPixmap *m_background;
};

#endif // DCPPAGE_H
