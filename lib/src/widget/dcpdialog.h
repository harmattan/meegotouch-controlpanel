#ifndef DCPDIALOG_H
#define DCPDIALOG_H
#include <DuiDialog>

class DcpDialog : public DuiDialog
{
public:
    DcpDialog();
    virtual ~DcpDialog();
    virtual void close();
};

#endif // DCPDIALOG_H
