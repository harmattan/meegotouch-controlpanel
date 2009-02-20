#include "duisettingsappletpage.h"

DuiSettingsAppletPage::DuiSettingsAppletPage() : DuiSettingsPage() 
{
    m_PageId = Pages::APPLET;
    m_Referer = Pages::NOPAGE;
}

void DuiSettingsAppletPage::createContent()
{
    DuiSettingsPage::createContent();
}

void DuiSettingsAppletPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);
}

void DuiSettingsAppletPage::init(const QString &appletBinary, 
				 const QString &appletMetaData,
				 const QString &appletId)
{
	Q_UNUSED(appletBinary);
	Q_UNUSED(appletMetaData);
	Q_UNUSED(appletId);

}
