#include <QtDebug>

#include "dcppage.h"
#include <QGraphicsLinearLayout>
#include <DuiSceneManager>
#include <DuiApplication>
#include <DuiApplicationWindow>

DcpPage::DcpPage() : DuiApplicationPage()
{
    setBackButtonEnabled(true);
}

DcpPage::~DcpPage()
{
}

void DcpPage::createContent()
{
    DuiApplicationPage::createContent();
    setObjectName("DcpPage");

    setBackButtonEnabled(true);

    createLayout();
}

void DcpPage::createLayout()
{
    new QGraphicsLinearLayout(Qt::Vertical, centralWidget());
//    layout->setContentsMargins(0.0,0.0,0.0,0.0);
}

void DcpPage::organizeContent(const Dui::Orientation& ori)
{
    Q_UNUSED(ori);
}

void DcpPage::append (QGraphicsWidget* widget)
{
    Q_ASSERT(mainLayout());
    mainLayout()->addItem(widget);
}

void DcpPage::remove (QGraphicsWidget* widget)
{
    widget->deleteLater();
}

void DcpPage::connectSignals()
{
   connect(this, SIGNAL(backButtonClicked()), this, SLOT(back()));
   connectOrientation();
}

void DcpPage::connectOrientation()
{
//   DuiSceneManager* manager = sceneManager();
   DuiSceneManager* manager =
       DuiApplication::activeApplicationWindow()->sceneManager();
   if (manager) {
       // handle orientation change:
       connect(manager, SIGNAL(orientationChanged (Dui::Orientation)),
               this, SLOT(organizeContent(Dui::Orientation)));
   } else {
       qWarning("orientation connect fails");
   }
}

void DcpPage::disconnectSignals()
{
    DuiSceneManager* manager = sceneManager();
    if (manager) {
        disconnect(manager, SIGNAL(orientationChanged (Dui::Orientation)),
                this, SLOT(organizeContent(Dui::Orientation)));
    }

    disconnect(this, SIGNAL(backButtonClicked()), this, SLOT(back()));
}

void DcpPage::back()
{
    emit openSubPage(referer());
}

/* this is where pages optimize their open up times
 * default implementation sets the correct orientation */
void DcpPage::reload()
{
    if (sceneManager()) {
        organizeContent(sceneManager()->orientation());
    }
}

QGraphicsLinearLayout* DcpPage::mainLayout()
{
    return (QGraphicsLinearLayout*)(centralWidget()->layout());
}

