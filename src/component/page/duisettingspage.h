#ifndef DUISETTINGSPAGE_H
#define DUISETTINGSPAGE_H

#include <DuiApplicationPage>

class DuiPannableViewport;
class DuiSettingsPage : public DuiApplicationPage
{
    Q_OBJECT
public:
    DuiSettingsPage();

    virtual void createContent();
    virtual void organizeContent(Dui::Orientation ori);
protected:
   DuiPannableViewport *m_Viewport;
};

#endif // DUISETTINGSPAGE_H
