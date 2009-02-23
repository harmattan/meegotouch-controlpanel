#ifndef DUIACCOUNTCOMPONENT_H
#define DUIACCOUNTCOMPONENT_H
#include "duisimplecomponent.h" 
class DuiImageLabel;
class QGraphicsSceneMouseEvent;
class DuiAccountComponent : public DuiSimpleComponent
{
    Q_OBJECT
public:
    explicit DuiAccountComponent(DuiSettingsCategory *category,
                                  const QString& title="",
                                  QGraphicsWidget *parent=0);
protected:
    virtual void createContents();
    virtual void mousePressEvent (QGraphicsSceneMouseEvent *event);
private:
    DuiImageLabel* m_Label;
    	
};
#endif //DUIACCOUNTCOMPONENT_H
