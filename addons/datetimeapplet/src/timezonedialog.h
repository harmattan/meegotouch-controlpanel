#ifndef TIMEZONEDIALOG_H
#define TIMEZONEDIALOG_H

#include "dcpcommondialog.h"

class DuiTextEdit;

class TimeZoneDialog : public DcpCommonDialog
{
    Q_OBJECT

public:
    TimeZoneDialog();
    virtual ~TimeZoneDialog();

protected:
    void initWidget();

private slots:
    virtual void clearTextEdit(DuiTextEdit *textEdit);    
};
#endif //TIMEZONEDIALOG_H

