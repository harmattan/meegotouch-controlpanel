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

private:
    DuiContainer *m_Container;
    DuiLabel *m_DateLabel;
    DuiLabel *m_WeekLabel;
};
#endif // DATEVIEW_H

