/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef TIMEVIEW_H
#define TIMEVIEW_H

#include "dcpwidget.h"

class SettingAlarm;
class DuiContainer;
class DcpTime;

class TimeView : public DcpWidget
{
    Q_OBJECT

public:
    TimeView(QGraphicsWidget *parent = 0);
    virtual bool back();
    virtual bool pagePans() { return false; }

protected:
    void initWidget();

private slots:
    void timeOrDateChanged();

private:
    DuiContainer *m_Container;

    SettingAlarm *m_TimePicker;
    DcpTime *dcpTime;
};

#endif // TIMEVIEW_H

