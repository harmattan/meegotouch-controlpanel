#ifndef DISPLAYDIALOG_H
#define DISPLAYDIALOG_H

#include "commondialog.h"

class DuiLayout;
class LanguageLabelButtonContainer;

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

private slots:
    virtual void removeContainer(LanguageLabelButtonContainer *container);
};
#endif //DISPLAYWIDGET_H
