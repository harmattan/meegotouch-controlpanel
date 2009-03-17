#ifndef SERVICESBUTTON_H
#define SERVICESBUTTON_H

#include <DuiWidget>
class DuiButton;

class ServicesButton : public DuiWidget
{
    Q_OBJECT

public:
    ServicesButton(QGraphicsWidget *parent = 0, const QString &title = "");

private:
    DuiButton *m_button;
};
#endif // SERVICESBUTTON_H
