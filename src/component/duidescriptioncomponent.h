#ifndef DUIDESCRIPTIONCOMPONENT_H
#define DUIDESCRIPTIONCOMPONENT_H

#include "duisettingscomponent.h"

class DuiLabel;
class DuiLinearLayout;

class DuiDescriptionComponent:public DuiSettingsComponent{
    Q_OBJECT
public:
    DuiDescriptionComponent(DuiSettingsCategory *category,
                            const QString& title="",
                            QGraphicsWidget *parent=0);

    virtual void setTitle(const QString& title);
    void setDescription(const QString& desc);

        // Composite Pattern Interface
    virtual void add(DuiSettingsComponent *){}
    virtual void remove(DuiSettingsComponent *){}

    virtual void paint (QPainter * painter,
                        const QStyleOptionGraphicsItem * option,
                        QWidget * widget = 0 );


protected:
    virtual void createContents();
protected slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);
private:
    DuiLinearLayout *m_Layout;
    DuiLabel *m_Description;
    DuiLabel *m_Caption;
};


#endif // DUIDESCRIPTIONCOMPONENT_H
