#ifndef DCPCOMPONENT_H
#define DCPCOMPONENT_H

#include <duiwidget.h>
#include "pages.h"

class DcpCategory;

class DcpComponent : public DuiWidget
{
    Q_OBJECT
public:
    explicit DcpComponent(DcpCategory *category,
                                  const QString& title="",
                                  QGraphicsWidget *parent=0);
    QString title() const {return m_Title;}
    virtual void setTitle(const QString& title) {m_Title = title;}
    void setSubPage(Pages::Handle subPage) {m_SubPage = subPage;}; 
    void setSubPage(Pages::Id id, const QString &param="") 
        {m_SubPage.id = id; m_SubPage.param = param;};
    Pages::Handle subPage() const {return m_SubPage;};
    // Composite Pattern Interface	
    virtual void add(DcpComponent *component)=0;
    virtual void remove(DcpComponent *component)=0;

    virtual DcpComponent* child(int i) const;
    DcpCategory* category() const {return 0;}

protected:
    virtual void createContents()=0;
protected slots:
    virtual void switchToSubPage();

signals:
    void openSubPage(Pages::Handle);

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

private:
    QString m_Title; 
    DcpCategory* m_Category; 
    Pages::Handle m_SubPage;
};
#endif //DCPCOMPONENT_H
