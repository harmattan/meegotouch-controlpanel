#ifndef DCPMAINPAGE_H
#define DCPMAINPAGE_H

#include "dcpcategorypage.h"
class DcpMainCategory;
class DcpMainPage : public DcpCategoryPage
{
    Q_OBJECT
public:
    DcpMainPage();
    virtual void createContent();
    virtual void reload();
};

#endif // DUISETTINGSMAINPAGE_H
