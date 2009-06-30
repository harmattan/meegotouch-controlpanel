#ifndef UPDATEBUTTON_H
#define UPDATEBUTTON_H

#include <DuiWidget>

class DuiLabel;

class UpdateButton : public DuiWidget
{
    Q_OBJECT

public:
    UpdateButton(DuiWidget *parent = 0);
    virtual ~UpdateButton();

protected:
    void initWidget();

protected slots:
    virtual void onOrientationChanged();

private:
    DuiLabel *m_AutomaticLabel;
};
#endif // UPDATEBUTTON_H

