#ifndef DCPAPPLETPAGE_H
#define DCPAPPLETPAGE_H

#include "dcppage.h"
#include "pages.h"
class DcpAppletMetadata;
class DcpWidget;
class DcpAppletPage : public DcpPage
{
    Q_OBJECT
public:
    DcpAppletPage(DcpAppletMetadata* metadata);
    virtual ~DcpAppletPage();
    virtual void createContent();
    DcpAppletMetadata* metadata() const {return m_Metadata;};
    void setMetadata(DcpAppletMetadata* metadata){m_Metadata = metadata;};
    virtual void setReferer(Pages::Id id, const QString &param="");

protected:
    virtual void initApplet();
private:
    DcpWidget *m_View;
    DcpAppletMetadata* m_Metadata;
};

#endif // DCPAPPLETPAGE_H
