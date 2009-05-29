#ifndef TIMEZONEDIALOG_H
#define TIMEZONEDIALOG_H

#include "dcpcommondialog.h"

class DuiTextEdit;
class TimeZoneContainer;

class TimeZoneDialog : public DcpCommonDialog
{
    Q_OBJECT

public:
    TimeZoneDialog();
    virtual ~TimeZoneDialog();

protected:
    void initWidget();

private:
    DuiTextEdit *m_TextEdit;
    TimeZoneContainer *m_TimeZoneContainer;

private slots:
    virtual void clearTextEdit(DuiTextEdit *textEdit); 
    virtual void filteringListItems();
};
#endif //TIMEZONEDIALOG_H

