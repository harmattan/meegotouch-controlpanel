#ifndef DCPDIALOG_H
#define DCPDIALOG_H

#include <duiwidget.h>
#include <QMessageBox>
class QEventLoop;

class DcpDialog : public DuiWidget
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

