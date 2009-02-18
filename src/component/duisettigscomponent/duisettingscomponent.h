#ifndef DUISETTINGSCOMPONENT_H
#define DUISETTINGSCOMPONENT_H

#include <DuiWidget>
#include "pages.h"

class DuiSettingsCategory;

class DuiSettingsComponent : public DuiWidget
{
    Q_OBJECT
public:
    explicit DuiSettingsComponent(DuiSettingsCategory *category,
                                  const QString& title="",
                                  QGraphicsWidget *parent=0);
    QString title() const {return m_Title;}
    virtual void setTitle(const QString& title) {m_Title = title;}
    void setSubPageId(Pages::Id subPageId) {m_SubPageId = subPageId;};          
    Pages::Id subPageId() const {return m_SubPageId;};                      
    // Composite Pattern Interface	
    virtual void add(DuiSettingsComponent *component)=0;
    virtual void remove(DuiSettingsComponent *component)=0;

    virtual DuiSettingsComponent* child(int i) const;
    DuiSettingsCategory* category() const {return 0;}

protected:
    virtual void createContents()=0;
    virtual void switchToSubPage(); 

signals:
    void openSubPage(Pages::Id subPageId);

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation)=0;

private:
    QString m_Title; 
    DuiSettingsCategory* m_Category; 
    Pages::Id m_SubPageId;
};
#endif //DUISETTINGSCOMPONENT_H
