#ifndef DCPAPPLETCATEGORYPAGE_H
#define DCPAPPLETCATEGORYPAGE_H

#include "dcpcategorypage.h"
#include "pages.h"

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
    virtual void reload();

protected:
    void addComponent(DcpAppletMetadata *metadata, bool odd);
    void loadContent();

private:
    QString m_AppletCategory;
    QString m_LoadedAppletCategory; // the appletcategory that has already been
                                    // loaded. same as m_AppletCategory if the
                                    // page's content is loaded
};

#endif // DCPAPPLETCATEGORYPAGE_H

