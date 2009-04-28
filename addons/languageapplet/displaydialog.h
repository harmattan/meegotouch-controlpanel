#ifndef DISPLAYDIALOG_H
#define DISPLAYDIALOG_H

#include "duidialog.h"

class DisplayDialog : public DuiDialog
{
    Q_OBJECT

public:
    DisplayDialog();
    virtual ~DisplayDialog();

protected:
    void initWidget();

protected slots:
    void onOrientationAngleChanged ();
};
#endif //DISPLAYWIDGET_H
