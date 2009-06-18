#include <QtDebug>

#include "dcppage.h"
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <DuiSceneManager>

DcpPage::DcpPage() : DuiApplicationPage()
{
    connect(DuiSceneManager::instance(),
            SIGNAL(orientationChanged (const Dui::Orientation &)),
            this, SLOT(organizeContent(const Dui::Orientation &)));
    qDebug() << "page alloc";
    setBackButtonEnabled(true);
}

DcpPage::~DcpPage()
{
    disconnect(this, SLOT(organizeContent(const Dui::Orientation &)));

    qDebug() << "page destroyal" << title() << (void*) this;
}

void DcpPage::createContent()
{
    qDebug() << "page createContent" << metaObject()->className()
             << (void*) this;
    DuiApplicationPage::createContent();
    setObjectName("DcpPage");

    setBackButtonEnabled(true);

    _createLayout();
}

void DcpPage::_createLayout()
{
    DuiLayout* layout = new DuiLayout();
    layout->setAnimator(0);
    m_MainLayout = new DuiLinearLayoutPolicy(layout, Qt::Vertical);
    m_MainLayout->setObjectName("Page");
    layout->setAnimator(0);
    layout->setPolicy(m_MainLayout);
    layout->setContentsMargins(0.0,0.0,0.0,0.0);
    centralWidget()->setLayout(layout);
}

void DcpPage::organizeContent(const Dui::Orientation& ori)
{
    Q_UNUSED(ori);
    qDebug() << "page organizeContent";
}

void DcpPage::append (QGraphicsWidget* widget) {
    Q_ASSERT(mainLayout());
    mainLayout()->addItemAtPosition(widget, mainLayout()->count());
}


void DcpPage::remove (QGraphicsWidget* widget) {
    DuiLayout* layout = (DuiLayout*)centralWidget()->layout();
    Q_ASSERT(layout);
    widget->deleteLater();
}

void DcpPage::back()
{
    emit openSubPage(referer());
}

