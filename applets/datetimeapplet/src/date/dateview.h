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

