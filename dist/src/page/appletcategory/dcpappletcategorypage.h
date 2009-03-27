#ifndef DCPAPPLETCATEGORYPAGE_H
#define DCPAPPLETCATEGORYPAGE_H

#include "dcpcategorypage.h" 
#include "pages.h"

class DcpAppletContainer;
class DcpAppletMetadata;

class DcpAppletCategoryPage : public DcpCategoryPage
{
    Q_OBJECT

public:
    DcpAppletCategoryPage(const QString &appletCategory);
    virtual ~DcpAppletCategoryPage();
    virtual void createContent();
    const QString appletCategory() const {return m_AppletCategory;};
    void setAppletCategory(const QString &appletCategory){m_AppletCategory=appletCategory;};

protected:
    void addComponent(DcpAppletMetadata *metadata);

private:
    QString m_AppletCategory;
    DcpAppletContainer *m_AppletContainer;
};

#endif // DCPAPPLETCATEGORYPAGE_H
