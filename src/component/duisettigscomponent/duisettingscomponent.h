#ifndef DUISETTINGSCOMPONENT_H
#define DUISETTINGSCOMPONENT_H

#include <DuiWidget>

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

    // Composite Pattern Interface	
    virtual void add(DuiSettingsComponent *component)=0;
    virtual void remove(DuiSettingsComponent *component)=0;

    virtual DuiSettingsComponent* child(int i) const;
    DuiSettingsCategory* category() const {return 0;}
protected:
    virtual void createContents()=0;
signals:
    void subPageOpen(int pageID);
protected slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation)=0;
private:
    QString m_Title; 
    DuiSettingsCategory* m_Category; 
};
#endif //DUISETTINGSCOMPONENT_H
