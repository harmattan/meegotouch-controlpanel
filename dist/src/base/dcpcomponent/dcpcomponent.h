#ifndef DCPCOMPONENT_H
#define DCPCOMPONENT_H

#include <DuiWidget>
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
    void setSubPageId(Pages::Id subPageId) {m_SubPageId = subPageId;};          
    Pages::Id subPageId() const {return m_SubPageId;};                      
    // Composite Pattern Interface	
    virtual void add(DcpComponent *component)=0;
    virtual void remove(DcpComponent *component)=0;

    virtual DcpComponent* child(int i) const;
    DcpCategory* category() const {return 0;}

protected:
    virtual void createContents()=0;
    virtual void switchToSubPage(); 

signals:
    void openSubPage(Pages::Id subPageId, const QString& param="");

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation)=0;

private:
    QString m_Title; 
    DcpCategory* m_Category; 
    Pages::Id m_SubPageId;
};
#endif //DCPCOMPONENT_H
