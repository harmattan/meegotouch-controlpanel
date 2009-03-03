#ifndef DCPACCOUNTCOMPONENT_H
#define DCPACCOUNTCOMPONENT_H
#include "dcpsimplecomponent.h" 
class DuiImageLabel;
class QGraphicsSceneMouseEvent;
class DcpAccountComponent : public DcpSimpleComponent
{
    Q_OBJECT
public:
    explicit DcpAccountComponent(DcpCategory *category,
                                  const QString& title="",
                                  QGraphicsWidget *parent=0);
protected:
    virtual void createContents();
    virtual void mousePressEvent (QGraphicsSceneMouseEvent *event);
private:
    // DuiImageLabel* m_Label;

private slots:
	virtual void handleClick(QString);
    	
};
#endif //DCPACCOUNTCOMPONENT_H
