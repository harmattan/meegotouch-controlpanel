#include "duisettingsmainpage.h"

#include <QtDebug>

#include <duilinearlayout.h>
#include <duilabel.h>
#include <duipannableviewport.h>

#include "duimaincategory.h"
#include "duidescriptioncomponent.h"
#include "duirecentlyusedcomponent.h"
#include "pages.h"


static const QString componentTexts[] = {
    DuiSettingsMainPage::tr("Personalization"), /* <- title */
    DuiSettingsMainPage::tr("<p>Personalize the device with e.g. "
                            "<font color=#e48415>profile, themes, fonts, "
                            "home screen, language etc.</font></p>"),
    DuiSettingsMainPage::tr("Connectivity"), /* <- title */
    DuiSettingsMainPage::tr("<p>Adjust connections of e.g. "
                            "<font color=#e48415>"
                            "Internet connection, Bluetooth, GPS etc.</font></p>"),
    DuiSettingsMainPage::tr("Display"), /* <- title */
    DuiSettingsMainPage::tr("<p>Adjust display appearance with e.g. "
                            "<font color=#e48415>Light "
                            "sensor, brightness etc.</font></p>"),
    DuiSettingsMainPage::tr("Sound"), /* <- title */
    DuiSettingsMainPage::tr("<p>Adjust tones for e.g. "
                            "<font color=#e48415>"
                            "Message alert, email "
                            "alert etc.</font></p>"),
    DuiSettingsMainPage::tr("Call"), /* <- title */
    DuiSettingsMainPage::tr("<p>Adjust settings with e.g. "
                            "<font color=#e48415>"
                            "call waiting, automatic redial etc.</font></p>"),
    DuiSettingsMainPage::tr("Date & Time"), /* <- title */
    DuiSettingsMainPage::tr("<p>Adjust Date & Time with e.g. "
                            "<font color=#e48415>"
                            "time format and timezone.</font></p>"),
    DuiSettingsMainPage::tr("Security"), /* <- title */
    DuiSettingsMainPage::tr("<p>Adjust phone security settings with e.g. "
                            "<font color=#e48415>passcode, privacy lock"
                            " etc.</font></p>"),
    DuiSettingsMainPage::tr("Device system"), /* <- title */
    DuiSettingsMainPage::tr("<p>View <font color=#e48415>"
                            "memory information</font> and "
                            "<font color=#e48415>backup / restore "
                            "data.</font></p>"),
    DuiSettingsMainPage::tr("Account"), /* <- title */
    DuiSettingsMainPage::tr("<p>Create your own service accounts in e.g. "
                            "<font color=#e48415>Ovi, Google, Yahooo "
                            "etc. </font>and adjust settings for "
                            "existing accounts,</p>"),
    DuiSettingsMainPage::tr("Application"), /* <- title */
    DuiSettingsMainPage::tr("<p>Adjust settings for each application e.g. "
                            "<font color=#e48415>Browser, Messaging, "
                            "Calendar etc.</font></p>"),
    QString()
};

static const QString resetSettingsTitle = DuiSettingsMainPage::tr(
                                                "Reset settings");
static const QString resetSettingsDescription = DuiSettingsMainPage::tr(
                                  "Reset network settings; Delete all media "
                                  "and data or reset all settings without "
                                  "deleting all media and data.");

static const QString settingsTitle = DuiSettingsMainPage::tr("Settings");


DuiSettingsMainPage::DuiSettingsMainPage()
{
}


void DuiSettingsMainPage::createContent()
{
    DuiSettingsPage::createContent();
    DuiLinearLayout* mainLayout = new DuiLinearLayout(Qt::Vertical);

    DuiLabel* title = new DuiLabel(settingsTitle);
    title->setAlignment(Qt::AlignCenter);
    title->setMaximumHeight(30);
    mainLayout->addItem(title);

    m_Category = new DuiMainCategory(settingsTitle);

    // most recent used items:
    DuiRecentlyUsedComponent* recentlyComp = new DuiRecentlyUsedComponent(
                                                    m_Category);
    m_Category->add(recentlyComp);

    // category descriptions:
    Q_ASSERT (sizeof (componentTexts) / sizeof(QString) % 4 == 1);
    for (int i=0; true; i+=4){
        QString title = componentTexts[i];
        if (title.isNull()) break;

        DuiDescriptionComponent *compo1 = new DuiDescriptionComponent(
                m_Category, title);
        compo1->setDescription(componentTexts[i+1]);
        compo1->setSubPageId(Pages::ACCOUNTS);
        connect(compo1, SIGNAL(openSubPage(Pages::Id)),
                this, SIGNAL(openSubPage(Pages::Id)));

        title = componentTexts[i+2];
        DuiDescriptionComponent *compo2 = new DuiDescriptionComponent(
                m_Category, title);
        compo2->setDescription(componentTexts[i+3]);
        m_Category->add(compo1, compo2);
    }

    // reset settings:
    DuiDescriptionComponent *resetSettings = new DuiDescriptionComponent(
            m_Category, resetSettingsTitle);
    resetSettings->setDescription(resetSettingsDescription);
    resetSettings->setFullRowSize ();
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
void DuiSettingsMainPage::onSizeChanged(const QSizeF & pannedWidgetSize,
                                    const QSizeF & pannableViewportSize)
{
    int width = pannableViewportSize.width();
    if (pannedWidgetSize.width() != width){
        m_Category->setMinimumSize(width, -1);
        m_Category->setMaximumSize(width, -1);
    }
}


