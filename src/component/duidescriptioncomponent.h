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
    ~DuiDescriptionComponent();

    virtual void setTitle(const QString& title);
    void setDescription(const QString& desc);
    void setTextAlignment(Qt::Alignment align);

        // Composite Pattern Interface
    virtual void add(DuiSettingsComponent *){}
    virtual void remove(DuiSettingsComponent *){}

    virtual void paint (QPainter * painter,
                        const QStyleOptionGraphicsItem * option,
                        QWidget * widget = 0 );
    void setFullRowSize();

protected:
    virtual void createContents();

protected slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);
private:
    DuiLinearLayout *m_Layout;
    DuiLabel *m_Description;
    DuiLabel *m_Caption;
    QPixmap *m_Background;
};


#endif // DUIDESCRIPTIONCOMPONENT_H
