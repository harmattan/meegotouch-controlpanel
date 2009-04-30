#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include "dcpdialog.h"
#include <QStringList>
class KeyboardDialog : public DcpDialog
{
    Q_OBJECT

public:
    KeyboardDialog();
    virtual ~KeyboardDialog();
    void close();
protected:
    void initWidget();

protected slots:
    void onOrientationAngleChanged();
private:
    class KeyboardWidget *m_Widget;
    QStringList m_OldLanguages;
};
#endif //KEYBOARDWIDGET_H
