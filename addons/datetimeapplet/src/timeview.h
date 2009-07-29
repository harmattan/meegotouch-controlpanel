#ifndef TIMEVIEW_H
#define TIMEVIEW_H

#include "dcpwidget.h"

#include <clock/settingalarm.h>

class DuiContainer;

class TimeView : public DcpWidget
{
    Q_OBJECT

public:
    TimeView(QGraphicsWidget *parent = 0);
    virtual ~TimeView();

protected:
    void initWidget();

private:
    DuiContainer *m_Container;

	SettingAlarm *m_TimePicker;


private slots:
    virtual void orientationChanged();
};
#endif // TIMEVIEW_H

