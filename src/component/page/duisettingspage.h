#ifndef DUISETTINGSPAGE_H
#define DUISETTINGSPAGE_H

#include <DuiApplicationPage>

class DuiSettingsPage : public DuiApplicationPage
{
    Q_OBJECT
public:
    DuiSettingsPage();

    virtual void createContent();
    virtual void organizeContent(Dui::Orientation ori);

};

#endif // DUISETTINGSPAGE_H
