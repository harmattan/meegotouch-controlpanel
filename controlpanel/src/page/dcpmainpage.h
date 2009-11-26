#ifndef DCPMAINPAGE_H
#define DCPMAINPAGE_H

#include <DcpCategoryPage>

class DcpMainCategory;
class DcpCategoryComponent;

class DcpMainPage : public DcpPage
{
    Q_OBJECT
public:
    DcpMainPage();
    virtual ~DcpMainPage();
    virtual void createContent();
    virtual void reload();
public slots:
    void back();
protected:
    virtual void retranslateUi();
    virtual void organizeContent(const Dui::Orientation& ori);
private:
    DcpCategoryComponent* m_RecentlyComp;
};

#endif // DCPMAINPAGE_H
