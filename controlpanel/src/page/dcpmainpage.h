#ifndef DCPMAINPAGE_H
#define DCPMAINPAGE_H

#include <DcpCategoryPage>

class DcpMainCategory;
class DcpCategoryComponent;

class DcpMainPage : public DcpCategoryPage
{
    Q_OBJECT
public:
    DcpMainPage();
    virtual ~DcpMainPage();
    virtual void createContent();
    virtual void reload();
public slots:
    void back();
protected slots:
    void onLocaleChanged();

private:
    DcpCategoryComponent* m_RecentlyComp;
};

#endif // DCPMAINPAGE_H
