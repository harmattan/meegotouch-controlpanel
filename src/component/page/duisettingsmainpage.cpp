#include "duisettingsmainpage.h"

#include <QtDebug>

#include <duilinearlayout.h>
#include <duilabel.h>
#include <duipannableviewport.h>

#include "duimaincategory.h"
#include "duidescriptioncomponent.h"
#include "pages.h"
static const QString componentTexts[] = {
    DuiSettingsMainPage::tr("Personalization"), /* <- title */
    DuiSettingsMainPage::tr("<font>Personalize the device with e.g. </font>"
                            "<font color=#e48415>profile, themes, fonts, "
                            "home screen, language etc.</font>"),
    DuiSettingsMainPage::tr("Connectivity"), /* <- title */
    DuiSettingsMainPage::tr("<font>Adjust connections of e.g. </font>"
                            "<font color='#e48415'>"
                            "Internet connection, Bluetooth, GPS etc.</font>"),
    DuiSettingsMainPage::tr("Display"), /* <- title */
    DuiSettingsMainPage::tr("<font>Adjust display appearance with e.g. </font>"
                            "<font color=#e48415>Light "
                            "sensor, brightness etc.</font>"),
    DuiSettingsMainPage::tr("Sound"), /* <- title */
    DuiSettingsMainPage::tr("<font>Adjust tones for e.g. </font>"
                            "<font color=#e48415>"
                            "Message alert, email "
                            "alert etc.</font>"),
    DuiSettingsMainPage::tr("Call"), /* <- title */
    DuiSettingsMainPage::tr("<font>Adjust settings with e.g. </font>"
                            "<font color=#e48415>"
                            "call waiting, automatic redial etc.</font>"),
    DuiSettingsMainPage::tr("Date & Time"), /* <- title */
    DuiSettingsMainPage::tr("<font>Adjust Date & Time with e.g. </font>"
                            "<font color=#e48415>"
                            "time format and timezone.</font>"),
    DuiSettingsMainPage::tr("Security"), /* <- title */
    DuiSettingsMainPage::tr("<font>Adjust phone security settings with e.g. "
                            "</font><font color=#e48415>passcode, privacy lock"
                            " etc.</font>"),
    DuiSettingsMainPage::tr("Device system"), /* <- title */
    DuiSettingsMainPage::tr("<font>View </font><font color=#e48415>"
                            "memory information</font><font> and </font>"
                            "<font color=#e48415>backup / restore "
                            "data.</font>"),
    DuiSettingsMainPage::tr("Account"), /* <- title */
    DuiSettingsMainPage::tr("<font>Create your own service accounts in e.g. "
                            "</font><font color=#e48415>Ovi, Google, Yahooo "
                            "etc. </font><font>and adjust settings for "
                            "existing accounts,</font>"),
    DuiSettingsMainPage::tr("Application"), /* <- title */
    DuiSettingsMainPage::tr("<font>Adjust settings for each application e.g. "
                            "</font><font color=#e48415>Browser, Messaging, "
                            "Calendar etc.</font>"),
    QString()
};

DuiSettingsMainPage::DuiSettingsMainPage()
{
}


void DuiSettingsMainPage::createContent()
{
    DuiSettingsPage::createContent();
    DuiLinearLayout* mainLayout = new DuiLinearLayout(Qt::Vertical);

    DuiLabel* title = new DuiLabel("Settings");
    title->setAlignment(Qt::AlignCenter);
    title->setMaximumHeight(30);
    mainLayout->addItem(title);

    m_Category = new DuiMainCategory(tr("Settings"));
    Q_ASSERT (sizeof (componentTexts) / sizeof(QString) % 4 == 1);
    for (int i=0; true; i+=4){
        QString title = componentTexts[i];
        if (title.isNull()) break;

        DuiDescriptionComponent *compo1 = new DuiDescriptionComponent(
                m_Category, title);
        compo1->setDescription(componentTexts[i+1]);
        compo1->setSubPageId(Pages::ACCOUNTS);
	connect(compo1, SIGNAL(openSubPage(Pages::Id)), this, SIGNAL(openSubPage(Pages::Id)));
        title = componentTexts[i+2];
        DuiDescriptionComponent *compo2 = new DuiDescriptionComponent(
                m_Category, title);
        compo2->setDescription(componentTexts[i+3]);
        m_Category->add(compo1, compo2);
    }

    // reset settings:
    DuiDescriptionComponent *resetSettings = new DuiDescriptionComponent(
            m_Category, "Reset settings");
    resetSettings->setDescription("Reset network settings; Delete all media "
                                  "and data or reset all settings without "
                                  "deleting all media and data.");
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


