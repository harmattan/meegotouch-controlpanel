#ifndef DCPDIALOG_H
#define DCPDIALOG_H

#include <duiscenewindow.h>
#include <QMessageBox>
class QEventLoop;

#warning DcpDialog, DcpCommonDialog is DEPRECATED and will be removed, switch to DuiDialog if you can, or implement your own
class DcpDialog : public DuiSceneWindow
{
    Q_OBJECT
public:
    DcpDialog(DuiWidget* parent = 0);
    virtual ~DcpDialog();
    virtual int exec();

public slots:
    virtual void accept () {done (QMessageBox::Ok); }
    virtual void done (int result);
    virtual void reject () {done (QMessageBox::Cancel); }

protected slots:
    virtual void onOrientationChange();

private:
    QEventLoop* m_Loop;
};

#endif // DCPDIALOG_H

