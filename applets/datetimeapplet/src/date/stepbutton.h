#ifndef STEPBUTTON_H
#define STEPBUTTON_H

#include <DuiButton>

class StepButton : public DuiButton 
{
    Q_OBJECT

public:
    typedef enum Type {
            Left = 0,
            Right
    };
    StepButton(StepButton::Type type, DuiWidget *parent = 0);
    virtual ~StepButton();
    //!reimp
    virtual void paint(QPainter *painter, 
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget = 0);
    //!reimp_end

private:
    StepButton::Type m_Type;
};
#endif // STEPBUTTON_H

