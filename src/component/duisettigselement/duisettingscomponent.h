#ifdef DUISETTINGSCOMPONENT_H
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
    QString title() const;
    virtual void setTitle(const QString& title);
    // Composite Pattern Interface	
    virtual void add(DuiSettingsComponent *component);
    virtual void remove(DuiSettingsComponent *component);
    virtual DuiSettingsComponent* child(int i) const {return 0;};
    DuiSettingsCategory* category() const {return 0;};
protected slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation)=0;
private:
    QString m_Title; 
    DuiSettingsCategory* m_Category; 
}
#endif //DUISETTINGSCOMPONENT_H
