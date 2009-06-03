#ifndef DCPBUTTON2TOGGLE_H
#define DCPBUTTON2TOGGLE_H

#include "dcpbutton2.h"

class DcpButton2Toggle: public DcpButton2 {
    Q_OBJECT
public:
    explicit DcpButton2Toggle(DuiWidget* parent = 0);

    virtual void setText2(const QString& text);
    virtual DuiLayout* createLayout();
    virtual void setSmallToggle(bool isOn);

signals:
    void smallToggled (bool isOn);

protected slots:
    void onSmallToggled (bool isOn);

private:
    DuiButton* m_ToggleButton;
    QString m_Text2;
};


#endif // DCPBUTTON2TOGGLE_H
