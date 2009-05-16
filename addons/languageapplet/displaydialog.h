#ifndef DISPLAYDIALOG_H
#define DISPLAYDIALOG_H

#include "commondialog.h"

class DuiLayout;

class DisplayDialog : public CommonDialog
{
    Q_OBJECT

public:
    DisplayDialog();
    virtual ~DisplayDialog();

protected:
    void initWidget();

private:
    DuiLayout *m_WidgetLayout;
};
#endif //DISPLAYWIDGET_H
