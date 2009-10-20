/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef DATEVIEW_H
#define DATEVIEW_H

#include "dcpwidget.h"
#include "../time/dcptime.h"

class DuiLabel;
class DuiContainer;

class DateView : public DcpWidget
{
    Q_OBJECT

public:
    DateView(QGraphicsWidget *parent = 0);
    virtual ~DateView();

    virtual bool back();

protected:
    void initWidget();
    virtual void retranslateUi();

public slots:

private slots:
    void daySelected(int year, int month, int day);

private:
    int year, month, day;

    DuiContainer *m_Container;

    DcpTime *dcpTime;
	class MonthWidget* m_MonthWidget;
};
#endif // DATEVIEW_H

