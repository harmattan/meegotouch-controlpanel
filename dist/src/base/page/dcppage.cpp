#include <QtDebug>

#include "dcppage.h"
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>

DcpPage::DcpPage() : DuiApplicationPage() 
{
    connect(DuiDeviceProfile::instance(), SIGNAL(orientationAngleChanged
                            (DuiDeviceProfile::DeviceOrientationAngle)),
            this, SLOT(onOrientationAngleChanged()));
}

DcpPage::~DcpPage() 
{
}

void DcpPage::createContent()
{
    DuiLayout* layout = new DuiLayout();
    m_MainLayout = new DuiLinearLayoutPolicy(layout, Qt::Vertical);
    layout->setPolicy(m_MainLayout);
    centralWidget()->setLayout(layout);
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
    centralWidget()->layout()->invalidate();
    centralWidget()->layout()->activate();
}

void DcpPage::onOrientationAngleChanged() {
    organizeContent(DuiDeviceProfile::instance()->orientation());
}

void DcpPage::append (QGraphicsWidget* widget) {
    Q_ASSERT(mainLayout());
    mainLayout()->addItemAtPosition(widget, mainLayout()->count());
}

