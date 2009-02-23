#include "dcpappletpage.h"

DcpAppletPage::DcpAppletPage() : DcpPage() 
{
    m_PageId = Pages::APPLET;
    m_Referer = Pages::NOPAGE;
}

void DcpAppletPage::createContent()
{
    DcpPage::createContent();
}

void DcpAppletPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);
}

void DcpAppletPage::init(const QString &appletBinary, 
				 const QString &appletMetaData,
				 const QString &appletId)
{
	Q_UNUSED(appletBinary);
	Q_UNUSED(appletMetaData);
	Q_UNUSED(appletId);

}
