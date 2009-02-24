#ifndef DCPSIMPLECOMPONENT_H
#define DCPSIMPLECOMPONENT_H
#include "dcpcomponent.h" 
class DcpSimpleComponent : public DcpComponent
{
    Q_OBJECT
public:
    explicit DcpSimpleComponent(DcpCategory *category,
                                  const QString& title="",
                                  QGraphicsWidget *parent=0);
    virtual void add(DcpComponent *component);
    virtual void remove(DcpComponent *component);
protected:
    virtual void createContents();
protected slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation){};
    	
};
#endif //DCPSIMPLECOMPONENT_H
