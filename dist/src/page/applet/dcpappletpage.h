#ifndef DCPAPPLETPAGE_H
#define DCPAPPLETPAGE_H

#include "dcppage.h" 
#include "pages.h"

class DcpAppletPage : public DcpPage
{
    Q_OBJECT
public:
    DcpAppletPage(const QString &appletBinary);
    virtual ~DcpAppletPage();
    virtual void createContent();
    virtual void organizeContent(Dui::Orientation ori);
    void init(const QString &appletBinary, const QString &appletMetaData="",
              const QString &appletId="");
private:
    DuiWidget *m_View;
};

#endif // DCPAPPLETPAGE_H
