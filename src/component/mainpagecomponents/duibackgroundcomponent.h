#ifndef DUIBACKGROUNDCOMPONENT_H
#define DUIBACKGROUNDCOMPONENT_H

#include "duisettingscomponent.h"

class DuiLabel;
class DuiLinearLayout;

class DuiBackgroundComponent: public DuiSettingsComponent
{
    Q_OBJECT
public:
    DuiBackgroundComponent(DuiSettingsCategory *category,
                            const QString& title="",
                            QGraphicsWidget *parent=0);
    ~DuiBackgroundComponent();

    virtual void setTitle(const QString& title);
    void setTitleAlignment(Qt::Alignment align);

        // Composite Pattern Interface
    virtual void add(DuiSettingsComponent *){}
    virtual void remove(DuiSettingsComponent *){}

    virtual void paint (QPainter * painter,
                        const QStyleOptionGraphicsItem * option,
                        QWidget * widget = 0 );

    virtual void createContents();

protected slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

protected:
    void addItem ( QGraphicsLayoutItem * item );

private:
    DuiLabel *m_Caption;
    QPixmap *m_Background;
    DuiLinearLayout *m_Layout;
};


#endif // DUIBACKGROUNDCOMPONENT_H
