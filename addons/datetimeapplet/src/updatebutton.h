#ifndef UPDATEBUTTON_H
#define UPDATEBUTTON_H

#include <DuiWidget>

class UpdateButton : public DuiWidget
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

protected slots:
    virtual void onOrientationChanged();
};
#endif // UPDATEBUTTON_H

