#ifndef DCPMAINPAGE_H
#define DCPMAINPAGE_H

#include "dcpcategorypage.h"

class DcpMainCategory;
class DcpRecentlyUsedComponent;

class DcpMainPage : public DcpCategoryPage
{
    Q_OBJECT
public:
    DcpMainPage();
    virtual void createContent();
    virtual void reload();
public slots:
    void back();

private:
    DcpRecentlyUsedComponent* m_RecentlyComp;
};

#endif // DUISETTINGSMAINPAGE_H
