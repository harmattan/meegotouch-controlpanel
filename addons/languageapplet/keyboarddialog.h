#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include "commondialog.h"

class DuiLayout;
class LanguageLabelButtonContainer;

class KeyboardDialog : public CommonDialog
{
    Q_OBJECT

public:
    KeyboardDialog();
    virtual ~KeyboardDialog();
    void close();

signals:
    void reopen();

protected:
    void initWidget();

private:
    DuiLayout *m_WidgetLayout;
    QStringList m_OldLanguages;

private slots:
    virtual void removeContainer(LanguageLabelButtonContainer *container);
};
#endif //KEYBOARDWIDGET_H
