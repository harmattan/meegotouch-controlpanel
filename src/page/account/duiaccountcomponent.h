#ifndef DUIACCOUNTCOMPONENT_H
#define DUIACCOUNTCOMPONENT_H
#include "duisimplecomponent.h" 
class DuiImageLabel;
class DuiAccountComponent : public DuiSimpleComponent
{
    Q_OBJECT
public:
    explicit DuiAccountComponent(DuiSettingsCategory *category,
                                  const QString& title="",
                                  QGraphicsWidget *parent=0);
protected:
    virtual void createContents();
private:
    DuiImageLabel* m_Label;
    	
};
#endif //DUIACCOUNTCOMPONENT_H
