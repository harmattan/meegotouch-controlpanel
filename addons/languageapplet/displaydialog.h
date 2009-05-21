#ifndef DISPLAYDIALOG_H
#define DISPLAYDIALOG_H

#include "dcpcommondialog.h"

class DuiLayout;

class DisplayDialog : public DcpCommonDialog
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
