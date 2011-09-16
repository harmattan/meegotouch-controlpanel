#include "dcppageopenbutton.h"
#include "pagefactory.h"

DcpPageOpenButton::DcpPageOpenButton (const PageHandle& handle,
                                      const QString& titleId):
    m_Handle (handle),
    m_TitleId (titleId)
{
    setStyleName ("CommonSingleButtonInverted");

    if (!m_TitleId.isEmpty()) {
        retranslateUi();
    }
}

void DcpPageOpenButton::onClicked()
{
    PageFactory::instance()->changePage (m_Handle);
}

void DcpPageOpenButton::retranslateUi()
{
    setText (qtTrId (qPrintable((m_TitleId))));
}

