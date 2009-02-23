#ifndef DCPACCOUNTPAGE_H
#define DCPACCOUNTPAGE_H

#include "dcpcategorypage.h"
class DuiMainCategory;
class DcpAccountPage : public DcpCategoryPage
{
    Q_OBJECT
public:
    DcpAccountPage();
    virtual void createContent();
};

#endif // DCPACCOUNTPAGE_H
