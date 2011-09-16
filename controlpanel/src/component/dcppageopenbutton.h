#ifndef DCPPAGEOPENBUTTON_H
#define DCPPAGEOPENBUTTON_H

#include <MButton>
#include "pages.h"

class DcpPageOpenButton: public MButton
{
    Q_OBJECT
public:
    DcpPageOpenButton (const PageHandle& handle,
                       const QString& titleId);

protected slots:
    void onClicked();

protected:
    void retranslateUi();

private:
    PageHandle m_Handle;
    QString m_TitleId;
};


#endif // DCPPAGEOPENBUTTON_H

