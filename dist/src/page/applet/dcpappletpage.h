#ifndef DCPAPPLETPAGE_H
#define DCPAPPLETPAGE_H

#include "dcppage.h"
#include "pages.h"

class DcpWidget;
class DcpAppletMetadata;
class DcpAppletLoader;
class DuiLabel;

class DcpAppletPage : public DcpPage
{
    Q_OBJECT
public:
    DcpAppletPage(DcpAppletMetadata *metadata);
    virtual ~DcpAppletPage();
    virtual void createContent();
    void setMetadata (DcpAppletMetadata *metadata);
    virtual void reload();

protected slots:
    void changeWidget(int widgetId);
    virtual void back();

private:
    void clearup();
    void load();
    bool loadApplet();

    DcpAppletMetadata *m_Metadata;
    DcpAppletMetadata *m_LoadedMetadata;
    DcpWidget *m_MainWidget;
    DcpAppletLoader* m_AppletLoader;
    DuiLabel *m_MissingLabel;
};

#endif // DCPAPPLETPAGE_H

