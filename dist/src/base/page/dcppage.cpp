#include <QtDebug>
#include <duipannableviewport.h>
#include <QGraphicsLayout>
#include <QGridLayout>
#include "duiwidgetview.h"

#include "dcppage.h"
#include "dcpbackgroundview.h"

DcpPage::DcpPage() : DuiApplicationPage() 
{
}

void DcpPage::createContent()
{    
    m_DesktopViewport = new DuiPannableViewport(Qt::Vertical, this);
    DcpBackgroundView *view = new DcpBackgroundView(m_DesktopViewport);
    m_DesktopViewport->setView(view);
}

void DcpPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);

    // make the layout reorganize its elements:
    QGraphicsLayout* layout = this->layout();
    if (!layout) return;
    layout->invalidate();
    layout->activate();
}

