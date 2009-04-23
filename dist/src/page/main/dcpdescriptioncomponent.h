#ifndef DCPDESCRIPTIONCOMPONENT_H
#define DCPDESCRIPTIONCOMPONENT_H

#include "dcpbackgroundcomponent.h"

class DcpDescriptionComponent:public DcpBackgroundComponent
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

protected:
    virtual void createContents();
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

private:
    void initSizes();
    DuiLabel *m_Description;
    bool m_IsFullRow;
    Dui::Orientation m_Orientation;
};


#endif // DCPDESCRIPTIONCOMPONENT_H
