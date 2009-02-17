#include "duisettingsmainpage.h"

#include <QtDebug>

#include <duilinearlayout.h>
#include <duilabel.h>
#include <duipannableviewport.h>

#include "duimaincategory.h"
#include "duidescriptioncomponent.h"

static const QString componentTexts[] = {
    DuiSettingsMainPage::tr("Personalization"), /* <- title */
    DuiSettingsMainPage::tr("Personalize the device with e.g. profile, "
                            "themes, fonts, home screen, language etc."),
    DuiSettingsMainPage::tr("Connectivity"), /* <- title */
    DuiSettingsMainPage::tr("Adjust connections of e.g. Internet connection, "
                            "Bluetooth, GPS etc."),
    DuiSettingsMainPage::tr("Display"), /* <- title */
    DuiSettingsMainPage::tr("Adjust display appearance with e.g. Light "
                            "sensor, brightness etc."),
    DuiSettingsMainPage::tr("Sound"), /* <- title */
    DuiSettingsMainPage::tr("Adjust tones for e.g. Message alert, email "
                            "alert etc."),
    DuiSettingsMainPage::tr("Call"), /* <- title */
    DuiSettingsMainPage::tr("Adjust settings with e.g. call waiting, "
                            "automatic redial etc."),
    DuiSettingsMainPage::tr("Date & Time"), /* <- title */
    DuiSettingsMainPage::tr("Adjust Date & Time with e.g. time format and "
                            "timezone."),
    DuiSettingsMainPage::tr("Security"), /* <- title */
    DuiSettingsMainPage::tr("Adjust phone security settings with e.g. "
                            "passcode, privacy lock etc."),
    DuiSettingsMainPage::tr("Device system"), /* <- title */
    DuiSettingsMainPage::tr("View memory information and backup/restore data."),
    DuiSettingsMainPage::tr("Account"), /* <- title */
    DuiSettingsMainPage::tr("Create your own service accounts in e.g. Ovi, "
                            "Google, Yahooo etc. and adjust settings for "
                            "existing accounts,"),
    DuiSettingsMainPage::tr("Application"), /* <- title */
    DuiSettingsMainPage::tr("Adjust settings for each application e.g. "
                            "Browser, Messaging, Calendar etc."),
    QString()
};

DuiSettingsMainPage::DuiSettingsMainPage()
{
}


void DuiSettingsMainPage::createContent()
{
    DuiSettingsPage::createContent();
    DuiLinearLayout* mainLayout = new DuiLinearLayout(Qt::Vertical);

    DuiLabel* title = new DuiLabel("Title");
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


