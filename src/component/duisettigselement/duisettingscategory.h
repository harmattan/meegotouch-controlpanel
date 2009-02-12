#ifdef DUISETTINGSCOMPONENT_H
#define DUISETTINGSCOMPONENT_H
#include <DuiWidget>
#include "duisettingscomponent.h"
class DuiSettingsCategory : public DuiSettingsComponent
{
    Q_OBJECT
public:
    explicit DuiSettingsCategory(const QString& title="",
                                 QGraphicsWidget *parent=0);
    // Composite Pattern Interface	
    virtual void add(DuiSettingsComponent *component);
    virtual void remove(DuiSettingsComponent *component);
    virtual DuiSettingsComponent* child(int i);
    DuiSettingsCategory* category() {return 0};
protected slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);
private:
    vector<DuiSettingsComponet*> m_Children; 
}
#endif //DUISETTINGSCOMPONENT_H
