#include <QtDebug>
#include <duipannableviewport.h>
#include <QGraphicsLayout>
#include <QGridLayout>

#include <duiwidgetview.h>
#include <duilabel.h>
#include <duilinearlayout.h>

#include "dcppage.h"


DcpPage::DcpPage() : DuiApplicationPage() 
{
}

DcpPage::~DcpPage() 
{
    // if (m_Title)
    //    delete m_Title;
}

void DcpPage::createContent()
{    
    m_MainLayout = new DuiLinearLayout(Qt::Vertical);
    centralWidget()->setLayout(m_MainLayout);

    /* m_Title = new DuiLabel("-");
    m_Title->setAlignment(Qt::AlignCenter);
    m_Title->setMaximumHeight(30);
    m_Title->setZValue(30);
    m_MainLayout->addItem(m_Title);*/
    centralWidget()->setLayout(m_MainLayout);
}


const QString 
DcpPage::title() const
{
    // return m_Title->text();
    return m_Title;
}

void
DcpPage::setTitle(const QString& title)
{
    // m_Title->setText(title);
    m_Title = title;
}

void DcpPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);

    // make the layout reorganize its elements:
    QGraphicsLayout* layout = this->layout();
    if (!layout) return;

    layout->setMinimumSize(DuiDeviceProfile::instance()->resolution());
    layout->setPreferredSize(DuiDeviceProfile::instance()->resolution());
    layout->setMaximumSize(DuiDeviceProfile::instance()->resolution());
//   layout->invalidate();
    layout->activate();
}

