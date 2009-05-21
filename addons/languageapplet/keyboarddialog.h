#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include "dcpcommondialog.h"

class DuiLayout;
class DcpLanguageSelectContainer;

class KeyboardDialog : public DcpCommonDialog
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
