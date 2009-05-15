#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include "commondialog.h"

class DuiLayout;
class DcpLanguageSelectContainer;

class KeyboardDialog : public CommonDialog
{
    Q_OBJECT

public:
    KeyboardDialog();
    virtual ~KeyboardDialog();
    QStringList selectedLanguages();

protected:
    void initWidget();

private:
    DuiLayout *m_WidgetLayout;
    DcpLanguageSelectContainer* m_SelectContainer;
};
#endif //KEYBOARDWIDGET_H
