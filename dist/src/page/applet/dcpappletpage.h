#ifndef DCPAPPLETPAGE_H
#define DCPAPPLETPAGE_H

#include "dcppage.h" 
#include "pages.h"

class DcpAppletPage : public DcpPage
{
    Q_OBJECT
public:
    DcpAppletPage();
    virtual void createContent();
    virtual void organizeContent(Dui::Orientation ori);
    void init(const QString &appletBinary, const QString &appletMetaData,
              const QString &appletId);
};

#endif // DCPAPPLETPAGE_H
