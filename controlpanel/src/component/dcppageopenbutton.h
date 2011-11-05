#ifndef DCPPAGEOPENBUTTON_H
#define DCPPAGEOPENBUTTON_H

#include <MButton>
#include "pages.h"

class DcpPageOpenButton: public MButton
{
    Q_OBJECT
    Q_PROPERTY (QString TDriverID READ TDriverID WRITE setTDriverID)
public:
    DcpPageOpenButton (const PageHandle& handle,
                       const QString& titleId);
    QString TDriverID() const { return m_TDriverID; }
    void setTDriverID(const QString &tdriverID) { m_TDriverID = tdriverID; }

protected slots:
    void onClicked();

protected:
    void retranslateUi();

private:
    PageHandle m_Handle;
    QString m_TitleId;
    QString m_TDriverID;
};


#endif // DCPPAGEOPENBUTTON_H

