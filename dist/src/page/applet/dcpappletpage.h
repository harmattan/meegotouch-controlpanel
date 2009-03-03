#ifndef DCPAPPLETPAGE_H
#define DCPAPPLETPAGE_H

#include "dcpcategorypage.h" 
#include "pages.h"

class DcpAppletPage : public DcpCategoryPage
{
    Q_OBJECT
public:
    DcpAppletPage(const QString &appletBinary);
    virtual ~DcpAppletPage();
    virtual void createContent();
    virtual void organizeContent(Dui::Orientation ori);
    const QString appletBinary() const {return m_AppletBinary;};
    void setAppletBinary(const QString &appletBinary){m_AppletBinary=appletBinary;};
protected:
    virtual void initApplet();
private:
    DuiWidget *m_View;
    QString m_AppletBinary;
};

#endif // DCPAPPLETPAGE_H
