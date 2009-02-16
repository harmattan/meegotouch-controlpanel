#ifndef DUISETTINGSMAINPAGE_H
#define DUISETTINGSMAINPAGE_H

#include "duisettingspage.h"

class DuiSettingsMainPage : public DuiSettingsPage
{
    Q_OBJECT
public:
    DuiSettingsMainPage();
    virtual void createContent();
//    virtual void organizeContent(Dui::Orientation ori);

};

#endif // DUISETTINGSMAINPAGE_H
