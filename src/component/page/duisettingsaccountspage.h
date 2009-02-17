#ifndef DUISETTINGSACCOUNTPAGE_H
#define DUISETTINGSACCOUNTPAGE_H

#include "duisettingscategorypage.h"
class DuiMainCategory;
class DuiSettingsAccountPage : public DuiSettingsCategoryPage
{
    Q_OBJECT
public:
    DuiSettingsAccountPage();
    virtual void createContent();
};

#endif // DUISETTINGSACCOUNTPAGE_H
