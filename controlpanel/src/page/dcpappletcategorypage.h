#ifndef DCPAPPLETCATEGORYPAGE_H
#define DCPAPPLETCATEGORYPAGE_H

#include <DcpPage>
#include <Pages>
#include "maintranslations.h"

class DcpAppletMetadata;
class DcpAppletButtons;

class DcpAppletCategoryPage :
        public DcpPage
{
    Q_OBJECT

public:
    DcpAppletCategoryPage (const DcpCategoryInfo *categoryInfo);
    virtual ~DcpAppletCategoryPage ();


    virtual void createContent ();
    const QString appletCategory () const;
    void setCategoryInfo (const DcpCategoryInfo *categoryInfo);

    virtual void reload();
    void setTitleId(const char* titleId);

public slots:
    virtual void back();

protected:
    virtual void retranslateUi();

private:
    // the appletcategory that has already been
    // loaded. same as m_CategoryInfo->appletCategory if the
    // page's content is loaded
    QString m_LoadedAppletCategory;
    const DcpCategoryInfo  *m_CategoryInfo;
    const char* m_TitleId;
    DcpAppletButtons* m_Category;
    friend class Ut_DcpAppletCategoryPage;
};

#endif

