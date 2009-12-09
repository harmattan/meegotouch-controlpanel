#ifndef APPLETERRORSDIALOG_H
#define APPLETERRORSDIALOG_H

#include <DuiDialog>

class AppletErrorsDialog: public DuiDialog
{
    Q_OBJECT
    AppletErrorsDialog();

public:
    static void showAppletErrors();
};

#endif // APPLETERRORSDIALOG_H

