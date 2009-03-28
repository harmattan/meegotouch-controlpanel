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
    layout->setAnimator(NULL);
    layout->setPolicy(m_MainLayout);
    centralWidget()->setLayout(layout);
    setBackButtonEnabled(true);
    layout->setContentsMargins(15,0,15,0);
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

