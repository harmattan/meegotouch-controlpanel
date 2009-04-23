#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include "duidialog.h"

class QPixmap;
class DuiLabel;

class KeyboardDialog : public DuiDialog
{
    Q_OBJECT

public:
    KeyboardDialog();
    ~KeyboardDialog();

protected:
    void initWidget();

protected slots:
    void onOrientationAngleChanged();

private:
    const QPixmap   *m_background;
    DuiLabel        *m_titleLabel;
};
#endif //KEYBOARDWIDGET_H
