#include <QtDebug>
#include <duipannableviewport.h>
#include <QGraphicsLayout>
#include <QGridLayout>
#include "duiwidgetview.h"
#include "duilabel.h"

#include "dcppage.h"
#include "dcpbackgroundview.h"

DcpPage::DcpPage() : DuiApplicationPage() 
{
}

void DcpPage::createContent()
{    
    m_DesktopViewport = new DuiPannableViewport(Qt::Vertical, this);
    m_BackgroundView = new DcpBackgroundView(m_DesktopViewport);
    m_DesktopViewport->setView(m_BackgroundView);
    m_Title = new DuiLabel("-");
    m_Title->setAlignment(Qt::AlignCenter);
    m_Title->setMaximumHeight(30);

}


const QString 
DcpPage::title() const
{
    return m_Title->text();
}

void
DcpPage::setTitle(const QString& title)
{
    m_Title->setText(title);
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

