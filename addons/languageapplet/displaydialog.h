#ifndef DISPLAYDIALOG_H
#define DISPLAYDIALOG_H

#include "dcpdialog.h"

class DisplayDialog : public DcpDialog
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
