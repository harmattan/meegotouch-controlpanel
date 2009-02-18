#ifndef DUIDESCRIPTIONCOMPONENT_H
#define DUIDESCRIPTIONCOMPONENT_H

#include "duibackgroundcomponent.h"

class DuiDescriptionComponent:public DuiBackgroundComponent
{
    Q_OBJECT
public:
    DuiDescriptionComponent(DuiSettingsCategory *category,
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
    virtual void polishEvent ();

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

private:
    DuiLabel *m_Description;
    bool m_IsFullRow;
    Dui::Orientation m_Orientation;
};


#endif // DUIDESCRIPTIONCOMPONENT_H
