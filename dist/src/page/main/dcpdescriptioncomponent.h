#ifndef DCPDESCRIPTIONCOMPONENT_H
#define DCPDESCRIPTIONCOMPONENT_H

#include "dcpcomponent.h"
class DuiContainer;

class DcpDescriptionComponent:public DcpComponent
{
    Q_OBJECT
public:
    DcpDescriptionComponent(DcpCategory *category,
                            const QString& title="",
                            QGraphicsWidget *parent=0);

    void setDescription(const QString& desc);
    void setTextAlignment(Qt::Alignment align);

    virtual void add(DcpComponent*){}
    virtual void remove(DcpComponent*){}
    virtual void setTitle(const QString& title);

protected:
    virtual void createContents();
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );

private:
    class DuiLabel *m_Description;
    Dui::Orientation m_Orientation;
    DuiContainer *m_Container;
};

#endif // DCPDESCRIPTIONCOMPONENT_H
