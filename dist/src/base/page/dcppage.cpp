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
    setBackButtonEnabled(true);

    _createLayout();
}

void DcpPage::_createLayout()
{
    DuiLayout* layout = new DuiLayout();
    m_MainLayout = new DuiLinearLayoutPolicy(layout, Qt::Vertical);
    layout->setAnimator(NULL);
    layout->setPolicy(m_MainLayout);
    centralWidget()->setLayout(layout);
    layout->setContentsMargins(12.0,0.0,12.0,0.0);
}

void DcpPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);
}

void DcpPage::onOrientationAngleChanged() {
    organizeContent(DuiDeviceProfile::instance()->orientation());
    qDebug() << "XXX" << size() << centralWidget()->size();
}

void DcpPage::append (QGraphicsWidget* widget) {
    Q_ASSERT(mainLayout());
    mainLayout()->addItemAtPosition(widget, mainLayout()->count());
}

void DcpPage::remove (QGraphicsWidget* widget) {
    // FIXME dui removeItem segfaults
    /*
    DuiLayout* layout = (DuiLayout*)centralWidget()->layout();
    Q_ASSERT(layout);
    layout->removeItem(widget);
    */
    Q_UNUSED(widget);
    _createLayout();
}

void DcpPage::back()
{
    emit openSubPage(referer());
}
