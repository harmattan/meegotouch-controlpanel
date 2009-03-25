#ifndef SERVICESBUTTON_H
#define SERVICESBUTTON_H

#include <DuiWidget>

class DuiGridLayout;
class DuiButton;
class DuiLabel;

class ServicesButton : public DuiWidget
{
    Q_OBJECT

public:
    ServicesButton(QGraphicsWidget *parent = 0, const QString &title = "");

    void resizeEvent(QGraphicsSceneResizeEvent *event);

private:
    DuiGridLayout   *m_mainLayout;
    DuiButton       *m_button;
    DuiLabel        *m_label;
};
#endif // SERVICESBUTTON_H
