#ifndef DCPBUTTONTOGGLE_H
#define DCPBUTTONTOGGLE_H

#include "dcpbuttonalign.h"

class DcpButtonToggle: public DcpButtonAlign {
    Q_OBJECT
public:
    explicit DcpButtonToggle(DuiWidget* parent = 0);

    virtual void setText2(const QString& text);
    virtual void setIconId(const QString& iconId);
    QString iconId();
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


#endif // DCPBUTTONTOGGLE_H
