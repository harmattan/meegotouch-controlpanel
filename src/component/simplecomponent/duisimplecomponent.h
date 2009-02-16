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
protected:
    virtual void createContents();
private:
    	
};
#endif //DUISETTINGSCOMPONENT_H
