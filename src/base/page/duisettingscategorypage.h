#ifndef DUISETTINGSCATEGORYPAGE_H
#define DUISETTINGSCATEGORYPAGE_H

#include "duisettingspage.h"
class DuiMainCategory;

class DuiSettingsCategoryPage : public DuiSettingsPage
{
    Q_OBJECT
public:
    DuiSettingsCategoryPage();
    virtual void createContent();

protected slots:
    void onSizeChanged(const QSizeF & size1, const QSizeF & size2);

protected:
    DuiMainCategory *m_Category;

};

#endif // DUISETTINGSCATEGORYPAGE_H
