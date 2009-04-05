#ifndef DCPAPPLETPAGE_H
#define DCPAPPLETPAGE_H

#include "dcppage.h"
#include "pages.h"
class DuiWidget;
class DcpAppletPage : public DcpPage
{
    Q_OBJECT
public:
    DcpAppletPage(DuiWidget* widget);
    virtual ~DcpAppletPage();
    virtual void createContent();
private:
    DuiWidget *m_MainWidget;
};

#endif // DCPAPPLETPAGE_H
