#ifndef DUISETTINGSMAINPAGE_H
#define DUISETTINGSMAINPAGE_H

#include "duisettingspage.h"
class DuiMainCategory;
class DuiSettingsMainPage : public DuiSettingsPage
{
    Q_OBJECT
public:
    DuiSettingsMainPage();
    virtual void createContent();
protected slots:
    void onSizeChanged(const QSizeF & size1, const QSizeF & size2);
private:
    DuiMainCategory *m_Category;

};

#endif // DUISETTINGSMAINPAGE_H
