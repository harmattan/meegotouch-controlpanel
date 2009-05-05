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
    DuiApplicationPage::createContent();

    setBackButtonEnabled(true);

    _createLayout();
}

void DcpPage::_createLayout()
{
    DuiLayout* layout = new DuiLayout();
    layout->setAnimator(NULL);
    m_MainLayout = new DuiLinearLayoutPolicy(layout, Qt::Vertical);
    layout->setAnimator(NULL);
    layout->setPolicy(m_MainLayout);
    layout->setContentsMargins(12.0,0.0,12.0,0.0);
    centralWidget()->setLayout(layout);
}

void DcpPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);
    qDebug() << "XXX organizeContent";
}

void DcpPage::onOrientationAngleChanged() {
    organizeContent(DuiDeviceProfile::instance()->orientation());
}

void DcpPage::append (QGraphicsWidget* widget) {
    Q_ASSERT(mainLayout());
    mainLayout()->addItemAtPosition(widget, mainLayout()->count());
}


void DcpPage::remove (QGraphicsWidget* widget) {
    DuiLayout* layout = (DuiLayout*)centralWidget()->layout();
    Q_ASSERT(layout);
    layout->removeItem(widget);
}

void DcpPage::back()
{
    emit openSubPage(referer());
}

