#include "duisettingspage.h"

#include <QtDebug>

#include <duilinearlayout.h>
#include <duilabel.h>
#include "duisimplecategory.h"
#include <duipannableviewport.h>


DuiSettingsPage::DuiSettingsPage()
{
}


void DuiSettingsPage::createContent()
{
    m_Viewport = new DuiPannableViewport(Qt::Vertical, this);
}


void DuiSettingsPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);  
    qDebug() << "WARNING: orientation change is not yet implemented";
}

