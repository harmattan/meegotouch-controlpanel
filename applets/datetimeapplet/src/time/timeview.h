#ifndef TIMEVIEW_H
#define TIMEVIEW_H

#include "dcpwidget.h"

class SettingAlarm;
class DuiContainer;

class TimeView : public DcpWidget
{
    Q_OBJECT

public:
    TimeView(QGraphicsWidget *parent = 0);
    virtual bool back();
    virtual bool pagePans() { return false; }

protected:
    void initWidget();

private:
    DuiContainer *m_Container;

	SettingAlarm *m_TimePicker;
};

#endif // TIMEVIEW_H

