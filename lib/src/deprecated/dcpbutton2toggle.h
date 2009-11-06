#ifndef DCPBUTTON2TOGGLE_H
#define DCPBUTTON2TOGGLE_H

#warning "DcpButton2Toggle is DEPRECATED, and will be removed soon! Use DcpButtonToggle instead."
#include "dcpbutton2align.h"

class DcpButton2Toggle: public DcpButton2Align {
    Q_OBJECT
public:
    explicit DcpButton2Toggle(DuiWidget* parent = 0);

    virtual void setText2(const QString& text);
    virtual void setSmallToggle(bool isOn);

signals:
    void smallToggled (bool isOn);

protected slots:
    void onSmallToggled (bool isOn);

protected:
    virtual QGraphicsLayout* createLayout();
    DuiButton* toggleButton();

private:
    QString m_Text2;
};


#endif // DCPBUTTON2TOGGLE_H
