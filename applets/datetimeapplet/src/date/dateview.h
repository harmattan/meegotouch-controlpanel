#ifndef DATEVIEW_H
#define DATEVIEW_H

#include "dcpwidget.h"

class DuiLabel;
class DuiContainer;

class DateView : public DcpWidget
{
    Q_OBJECT

public:
    DateView(QGraphicsWidget *parent = 0);
    virtual ~DateView();

protected:
    void initWidget();

public slots:

private:
    DuiContainer *m_Container;

	class MonthWidget* m_MonthWidget;
};
#endif // DATEVIEW_H

