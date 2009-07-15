#include <QtDebug>

#include "dcppage.h"
#include <DuiSceneManager>
#include <QGraphicsLinearLayout>

DcpPage::DcpPage() : DuiApplicationPage()
{
    qDebug() << "page alloc";
    setBackButtonEnabled(true);
}

DcpPage::~DcpPage()
{
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
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(centralWidget());
    layout->setContentsMargins(0.0,0.0,0.0,0.0);
}

void DcpPage::organizeContent(const Dui::Orientation& ori)
{
    Q_UNUSED(ori);
    qDebug() << "page organizeContent";
}

void DcpPage::append (QGraphicsWidget* widget) {
    Q_ASSERT(mainLayout());
    mainLayout()->addItem(widget);
}


void DcpPage::remove (QGraphicsWidget* widget) {
    widget->deleteLater();
}

void DcpPage::connectSignals()
{
    connect(DuiSceneManager::instance(),
            SIGNAL(orientationChanged (const Dui::Orientation &)),
            this, SLOT(organizeContent(const Dui::Orientation &)));
    connect(this, SIGNAL(backButtonClicked()), this, SLOT(back()));
}

void DcpPage::disconnectSignals()
{
    disconnect(DuiSceneManager::instance(),
            SIGNAL(orientationChanged (const Dui::Orientation &)),
            this, SLOT(organizeContent(const Dui::Orientation &)));
    disconnect(this, SIGNAL(backButtonClicked()), this, SLOT(back()));
}

void DcpPage::back()
{
    emit openSubPage(referer());
}

/* this is where pages optimize their open up times
 * default implementation drops fatal error */
void DcpPage::reload()
{
    Q_ASSERT_X(!isContentCreated(), Q_FUNC_INFO,
            qPrintable(QString("not implemented for ")+metaObject()->className()));
}

QGraphicsLinearLayout* DcpPage::mainLayout()
{
    return (QGraphicsLinearLayout*)(centralWidget()->layout());
}

