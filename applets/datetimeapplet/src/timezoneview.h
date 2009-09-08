#ifndef TIMEZONEVIEW_H
#define TIMEZONEVIEW_H

#include "dcpwidget.h"

class DuiTextEdit;
class DcpTable;

class TimeZoneView : public DcpWidget
{
    Q_OBJECT

public:
    TimeZoneView(QGraphicsWidget *parent = 0);
    virtual ~TimeZoneView();
    virtual bool pagePans() const { return false; }

protected:
    void initWidget();

private:
    DuiTextEdit *m_TextEdit;
    DcpTable *m_Table;

private slots:
    virtual void orientationChanged();
    virtual void clearTextEdit(DuiTextEdit *textEdit);
    virtual void filteringListItems();
};

#endif // TIMEZONEVIEW_H

