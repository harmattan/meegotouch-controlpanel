#ifndef DCPMAINPAGE_H
#define DCPMAINPAGE_H

#include "dcppage.h"
class DcpMainCategory;
class DcpMainPage : public DcpPage
{
    Q_OBJECT
public:
    DcpMainPage();
    virtual void createContent();
    virtual void organizeContent(Dui::Orientation ori);

protected slots:
    void onSizeChanged(const QSizeF & size1, const QSizeF & size2);
    void onResetSettingsClicked();

private:
    DcpMainCategory *m_Category;

};

#endif // DUISETTINGSMAINPAGE_H
