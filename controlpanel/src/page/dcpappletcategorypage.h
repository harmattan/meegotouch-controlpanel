#ifndef DCPAPPLETCATEGORYPAGE_H
#define DCPAPPLETCATEGORYPAGE_H

#include <DcpCategoryPage>
#include <Pages>
#include "maintranslations.h"

class DcpAppletMetadata;

class DcpAppletCategoryPage : 
        public DcpCategoryPage
{
    Q_OBJECT

public:
    DcpAppletCategoryPage (const DcpCategoryInfo *categoryInfo);
    virtual ~DcpAppletCategoryPage ();


    virtual void createContent ();
    const QString appletCategory () const;
    void setCategoryInfo (const DcpCategoryInfo *categoryInfo);

    virtual void reload();
    void cleanup();
    void setTitleId(const char* titleId);

public slots:
    virtual void back();

protected:
    virtual void retranslateUi();
    void addComponent (DcpAppletMetadata *applet);
    void loadContent ();

private:
    // the appletcategory that has already been
    // loaded. same as m_CategoryInfo->appletCategory if the
    // page's content is loaded
    QString m_LoadedAppletCategory; 
    const DcpCategoryInfo  *m_CategoryInfo;
    const char* m_TitleId;
};

#endif

