#include <QtDebug>

#include <duilinearlayout.h>

#include "dcppage.h"


DcpPage::DcpPage() : DuiApplicationPage() 
{
}

DcpPage::~DcpPage() 
{
}

void DcpPage::createContent()
{    
    m_MainLayout = new DuiLinearLayout(Qt::Vertical);
    centralWidget()->setLayout(m_MainLayout);
/*
    m_Title = new DuiLabel("-");
    m_Title->setAlignment(Qt::AlignCenter);
    m_Title->setMaximumHeight(30);
    m_Title->setZValue(30);
    m_MainLayout->addItem(m_Title);
 */
}


const QString 
DcpPage::title() const
{
    return m_Title;
}

void
DcpPage::setTitle(const QString& title)
{
    m_Title = title;
}

void DcpPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);

/*
    // make the layout reorganize its elements:
    QGraphicsLayout* layout = this->mainLayout();
    DuiWidget* widget = this->centralWidget();
    if (!widget || !layout) return;

    QSize size = DuiDeviceProfile::instance()->resolution();
    size.setHeight(1500);
    widget->setMinimumSize(size);
    widget->setPreferredSize(size);
    widget->setMaximumSize(size);
*/

/*
    layout->invalidate();
    layout->activate();
 */
}

