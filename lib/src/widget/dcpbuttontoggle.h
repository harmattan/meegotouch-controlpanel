/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPBUTTONTOGGLE_H
#define DCPBUTTONTOGGLE_H

#include "dcpbuttonalign.h"
class DuiButton;

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
