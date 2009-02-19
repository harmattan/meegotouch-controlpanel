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
    virtual void organizeContent(Dui::Orientation ori);

protected slots:
    void onSizeChanged(const QSizeF & size1, const QSizeF & size2);
    void onResetSettingsClicked();

private:
    DuiMainCategory *m_Category;

};

#endif // DUISETTINGSMAINPAGE_H
