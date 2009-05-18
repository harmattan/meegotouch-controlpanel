#ifndef UPDATEBUTTON_H
#define UPDATEBUTTON_H

#include <duibutton.h>

class UpdateButton : public DuiButton
{
    Q_OBJECT

public:
    UpdateButton(DuiWidget *parent = 0);
    virtual ~UpdateButton();
    //! \reimp
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget = 0);
    //! \reimp_end

protected:
    void initWidget();
};
#endif // UPDATEBUTTON_H

