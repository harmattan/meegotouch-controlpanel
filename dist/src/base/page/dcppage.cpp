#include <QtDebug>

#include "dcppage.h"
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>

DcpPage::DcpPage() : DuiApplicationPage() 
{
    connect(DuiDeviceProfile::instance(), SIGNAL(orientationAngleChanged
                            (DuiDeviceProfile::DeviceOrientationAngle)),
            this, SLOT(onOrientationAngleChanged()));
    qDebug() << "XXX page alloc";
    setBackButtonEnabled(true);
}

DcpPage::~DcpPage() 
{
    qDebug() << "XXX page destroyal" << title() << (void*) this;
}

void DcpPage::createContent()
{
    qDebug() << "XXX page createContent" << metaObject()->className()
             << (void*) this;
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
}

void DcpPage::onOrientationAngleChanged() {
    organizeContent(DuiDeviceProfile::instance()->orientation());
}

void DcpPage::append (QGraphicsWidget* widget) {
    Q_ASSERT(mainLayout());
    mainLayout()->addItemAtPosition(widget, mainLayout()->count());
}

void DcpPage::remove (QGraphicsWidget* widget) {
    Q_ASSERT(mainLayout());
}

void DcpPage::back()
{
    emit openSubPage(referer());
}
