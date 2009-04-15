#ifndef DISPLAYDIALOG_H
#define DISPLAYDIALOG_H

#include "duidialog.h"

class QPixmap;

class DisplayDialog : public DuiDialog
{
    Q_OBJECT

public:
    DisplayDialog();
    ~DisplayDialog();

protected:
    void initWidget();

private:
    const QPixmap   *m_background;
};
#endif //DISPLAYWIDGET_H
