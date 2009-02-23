#ifndef DCPCATEGORYPAGE_H
#define DCPCATEGORYPAGE_H

#include "dcppage.h"
class DcpMainCategory;

class DcpCategoryPage : public DcpPage
{
    Q_OBJECT
public:
    DcpCategoryPage();
    virtual void createContent();

protected slots:
    void onSizeChanged(const QSizeF & size1, const QSizeF & size2);

protected:
    DcpMainCategory *m_Category;

};

#endif // DCPCATEGORYPAGE_H
