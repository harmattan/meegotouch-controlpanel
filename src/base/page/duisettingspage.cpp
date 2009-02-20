#include <QtDebug>
#include <duipannableviewport.h>
#include <QGraphicsLayout>
#include <QGridLayout>
#include "duiwidgetview.h"

#include "duisettingspage.h"
#include "duibackgroundview.h"

DuiSettingsPage::DuiSettingsPage() : DuiApplicationPage() 
{
}

void DuiSettingsPage::createContent()
{    
    m_DesktopViewport = new DuiPannableViewport(Qt::Vertical, this);
    DuiBackgroundView *view = new DuiBackgroundView(m_DesktopViewport);
    m_DesktopViewport->setView(view);
}

void DuiSettingsPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);

    // make the layout reorganize its elements:
    QGraphicsLayout* layout = this->layout();
    if (!layout) return;
    layout->invalidate();
    layout->activate();
}

