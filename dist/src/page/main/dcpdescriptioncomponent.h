#ifndef DCPDESCRIPTIONCOMPONENT_H
#define DCPDESCRIPTIONCOMPONENT_H

#include "dcpcomponent.h"

class DcpDescriptionComponent:public DcpComponent
{
    Q_OBJECT
public:
    DcpDescriptionComponent(DcpCategory *category,
                            const QString& title="",
                            QGraphicsWidget *parent=0);

    void setDescription(const QString& desc);
    void setTextAlignment(Qt::Alignment align);

    void setFullRowSize();
    void setHalfRowSize();
    virtual void add(DcpComponent*){}
    virtual void remove(DcpComponent*){}

protected:
    virtual void createContents();
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

private:
    void initSizes();
    class DuiLabel *m_Description;
    bool m_IsFullRow;
    Dui::Orientation m_Orientation;
};


#endif // DCPDESCRIPTIONCOMPONENT_H

