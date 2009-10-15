#include <QtDebug>

#include "dcppage.h"
#include <DuiSceneManager>
#include <QGraphicsLinearLayout>

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
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(centralWidget());
    layout->setContentsMargins(0.0,0.0,0.0,0.0);
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

   Q_ASSERT (DuiSceneManager::instance());
   // handle orientation change:
   connect(	DuiSceneManager::instance(),
            SIGNAL(orientationChanged (const Dui::Orientation &)),
            this, 
			SLOT(organizeContent(const Dui::Orientation &)));
}

void DcpPage::disconnectSignals()
{
    disconnect(	DuiSceneManager::instance(),
            	SIGNAL(orientationChanged (const Dui::Orientation &)),
            	this,
				SLOT(organizeContent(const Dui::Orientation &)));

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
    organizeContent(DuiSceneManager::instance()->orientation());
}

QGraphicsLinearLayout* DcpPage::mainLayout()
{
    return (QGraphicsLinearLayout*)(centralWidget()->layout());
}
