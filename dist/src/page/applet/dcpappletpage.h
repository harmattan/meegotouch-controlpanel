#ifndef DCPAPPLETPAGE_H
#define DCPAPPLETPAGE_H

#include "dcppage.h"
#include "pages.h"
class DcpWidget;
class DcpAppletMetadata;
class DcpAppletLoader;
class DcpAppletPage : public DcpPage
{
    Q_OBJECT
public:
    DcpAppletPage(DcpAppletMetadata *metadata);
    virtual ~DcpAppletPage();
    virtual void createContent();

protected slots:
    void changeWidget(int widgetId);
    virtual void back();

protected slots:
    bool loadApplet();
    virtual void organizeContent(const Dui::Orientation& ori);

private:
    void setUpMainWidgetSize();

    DcpAppletMetadata *m_Metadata;
    DcpWidget *m_MainWidget;
    DcpAppletLoader* m_AppletLoader;
};

#endif // DCPAPPLETPAGE_H
