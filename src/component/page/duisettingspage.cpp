#include <QtDebug>
#include <duipannableviewport.h>

#include "duisettingspage.h"


DuiSettingsPage::DuiSettingsPage()
{
}


void DuiSettingsPage::createContent()
{
    m_DesktopViewport = new DuiPannableViewport(Qt::Vertical, this);
}




void DuiSettingsPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);
    qDebug() << "WARNING: orientation change is not yet implemented";
}

