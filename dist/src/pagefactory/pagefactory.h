#ifndef PAGEFACTORY_H
#define PAGEFACTORY_H

#include "dcppage.h"
#include "pages.h"
class DcpPage;
class DcpAppletMetadata;
class DcpAppletLoader;
class DcpWidget;
class PageFactory : public QObject
{
    Q_OBJECT
public:
    static PageFactory *instance();
    static DcpPage* page(DuiApplicationPage *page);
    DcpPage* create (Pages::Id pageId, const QString &param);
    bool backFromApplet();
signals:
    void changePage(DcpPage *page);
protected:
    PageFactory();
    bool loadApplet(DcpAppletMetadata *metadata);
    DcpPage* createMainPage();	
    DcpPage* createAppletPage(DcpAppletMetadata *metadata);
    DcpPage* createAppletPageFromCategory(DcpAppletMetadata *metadata);
    DcpPage* createAppletPageFromMostUsed(DcpAppletMetadata *metadata);
    DcpPage* createAppletCategoryPage(const QString& appletCategory);
protected slots:
    void changeAppletWidget(int widgetId);
private:
    DcpWidget *m_AppletWidget; 
    static PageFactory* sm_Instance;
    static DcpAppletLoader* sm_AppletLoader;
    
};

#endif // PAGEFACTORY_H
