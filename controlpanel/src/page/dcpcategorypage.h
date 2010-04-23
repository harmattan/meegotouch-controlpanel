#ifndef DCPCATEGORYPAGE_H
#define DCPCATEGORYPAGE_H

#include "dcppage.h"
class DcpMainCategory;

/*!
 * FIXME: this class is just an empty shell?
 */
class DcpCategoryPage : public DcpPage
{
    Q_OBJECT
public:
    DcpCategoryPage();
    virtual void createContent();

protected:
    DcpMainCategory *m_Category;
    friend class Ut_DcpCategoryPage;
};

#endif
