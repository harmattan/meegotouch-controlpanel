#include "dcpmainpage.h"

#include <QtDebug>

#include <duilinearlayout.h>
#include <duimultilayout.h>
#include <duilabel.h>
#include <duipannableviewport.h>

#include "dcpmaincategory.h"
#include "dcpdescriptioncomponent.h"
#include "dcprecentlyusedcomponent.h"
#include "pages.h"
#include "maintranslations.h"

DcpMainPage::DcpMainPage() :
	DcpPage()
{
    m_PageId = Pages::MAIN;
    m_Referer = Pages::NOPAGE;
}


void DcpMainPage::createContent()
{
    DcpPage::createContent();
    DuiLinearLayout* mainLayout = new DuiLinearLayout(Qt::Vertical);

    DuiLabel* title = new DuiLabel(Dcp::settingsTitle);
    title->setAlignment(Qt::AlignCenter);
    title->setMaximumHeight(30);
    mainLayout->addItem(title);

    m_Category = new DcpMainCategory(Dcp::settingsTitle);

    // most recent used items:
    DcpRecentlyUsedComponent* recentlyComp = new DcpRecentlyUsedComponent(
                                                    m_Category);
    m_Category->add(recentlyComp);

    // category descriptions:
    Q_ASSERT (sizeof (Dcp::componentTexts) / sizeof(QString) % 4 == 1);
    for (int i=0; true; i+=4){
        QString title = Dcp::componentTexts[i];
        if (title.isNull()) break;

        DcpDescriptionComponent *compo1 = new DcpDescriptionComponent(
                m_Category, title);
        compo1->setDescription(Dcp::componentTexts[i+1]);
        compo1->setSubPageId(Pages::ACCOUNTS);
        connect(compo1, SIGNAL(openSubPage(Pages::Id)),
                this, SIGNAL(openSubPage(Pages::Id)));

        title = Dcp::componentTexts[i+2];
        DcpDescriptionComponent *compo2 = new DcpDescriptionComponent(
                m_Category, title);
        compo2->setDescription(Dcp::componentTexts[i+3]);
        m_Category->add(compo1, compo2);
    }

    // reset settings:
    DcpDescriptionComponent *resetSettings = new DcpDescriptionComponent(
            m_Category, Dcp::resetSettingsTitle);
    resetSettings->setDescription(Dcp::resetSettingsDescription);
    resetSettings->setFullRowSize ();
    connect(resetSettings, SIGNAL(openSubPage(Pages::Id)),
            this, SLOT(onResetSettingsClicked()));
    m_Category->add(resetSettings);

    connect (m_DesktopViewport,
             SIGNAL(sizeChanged(const QSizeF &, const QSizeF &)),
             this, SLOT(onSizeChanged(const QSizeF &, const QSizeF &)));
    m_DesktopViewport->setWidget(m_Category);


    mainLayout->addItem(m_DesktopViewport);

    setLayout(mainLayout);
}


/* This function is responsible for keeping the width of the panned widget
   and its viewport the same. */
void DcpMainPage::onSizeChanged(const QSizeF & pannedWidgetSize,
                                    const QSizeF & pannableViewportSize)
{
    int width = pannableViewportSize.width();
    if (pannedWidgetSize.width() != width){
        m_Category->setMinimumSize(width, -1);
        m_Category->setMaximumSize(width, -1);
    }
}

void DcpMainPage::organizeContent(Dui::Orientation ori)
{
    DcpPage::organizeContent(ori);

    m_Category->onOrientationChange(ori);
}


// ----- FOR TESTING -----
#include <duideviceprofile.h>
void DcpMainPage::onResetSettingsClicked()
{
    DuiDeviceProfile *profile = DuiDeviceProfile::instance();
    if ( profile->orientation() == Dui::Portrait ) {
        qDebug() << "XXX mode changes to Angle0";
        profile->setOrientationAngle (DuiDeviceProfile::Angle0);
    } else {
        qDebug() << "XXX mode changes to Angle90";
        profile->setOrientationAngle (DuiDeviceProfile::Angle90);
    }
}
// --

