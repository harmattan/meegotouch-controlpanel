#ifndef DCPAPPLETCATEGORYPAGE_H
#define DCPAPPLETCATEGORYPAGE_H

#include "dcpcategorypage.h" 
#include "pages.h"

class DcpAppletCategoryPage : public DcpCategoryPage
{
    Q_OBJECT
public:
    DcpAppletCategoryPage(const QString &appletCategory);
    virtual ~DcpAppletCategoryPage();
    virtual void createContent();
    virtual void organizeContent(Dui::Orientation ori);
    const QString appletCategory() const {return m_AppletCategory;};
    void setAppletCategory(const QString &appletCategory){m_AppletCategory=appletCategory;};
private:
    QString m_AppletCategory;
};

#endif // DCPAPPLETCATEGORYPAGE_H
