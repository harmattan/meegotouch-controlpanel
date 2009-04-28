#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include "duidialog.h"

class KeyboardDialog : public DuiDialog
{
    Q_OBJECT

public:
    KeyboardDialog();
    virtual ~KeyboardDialog();

protected:
    void initWidget();

protected slots:
    void onOrientationAngleChanged();
};
#endif //KEYBOARDWIDGET_H
