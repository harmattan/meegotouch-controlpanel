#ifndef DUISETTINGSPAGE_H
#define DUISETTINGSPAGE_H

#include <DuiApplicationPage>
#include "pages.h"
class DuiPannableViewport;
class DuiSettingsPage : public DuiApplicationPage
{
    Q_OBJECT
public:
    DuiSettingsPage();

    virtual void createContent();
    virtual void organizeContent(Dui::Orientation ori);
signals:
    void openSubPage(Pages::Id subPageId);
protected:
   DuiPannableViewport *m_DesktopViewport;

private:
};

#endif // DUISETTINGSPAGE_H
