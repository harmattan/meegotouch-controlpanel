#include "dcpdialog.h"
DcpDialog::DcpDialog() : DuiDialog()
{}

DcpDialog::~DcpDialog()
{}

void DcpDialog::close()
{
    done(0);
}
