#ifndef DUISIMPLECOMPONENT_H
#define DUISIMPLECOMPONENT_H
#include "duisettingscomponent.h" 
class DuiSimpleComponent : public DuiSettingsComponent
{
    Q_OBJECT
public:
    explicit DuiSimpleComponent(DuiSettingsCategory *category,
                                  const QString& title="",
                                  QGraphicsWidget *parent=0);
    virtual void add(DuiSettingsComponent *component){};
    virtual void remove(DuiSettingsComponent *component){};
protected:
    virtual void createContents();
protected slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation){};
    	
};
#endif //DUISETTINGSCOMPONENT_H
