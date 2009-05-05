#include "displaydialog.h"
#include "languagetranslation.h"
#include "languageselectcontainer.h"
#include "languagelabelbuttoncontainer.h"
#include "dcplanguage.h"
#include "dcplanguageconf.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>

DisplayDialog::DisplayDialog()
              :CommonDialog(DcpLanguage::SelectDisplayText)
{
    initWidget();
}

DisplayDialog::~DisplayDialog()
{
}

void DisplayDialog::initWidget()
{
    // centralWidget
    DuiWidget *centralWidget = new DuiWidget(this);
    m_WidgetLayout = new DuiLayout(centralWidget);
    m_WidgetLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *widgetLayoutPolicy = 
        new DuiLinearLayoutPolicy(m_WidgetLayout, Qt::Vertical);
    m_WidgetLayout->setPolicy(widgetLayoutPolicy);
    centralWidget->setLayout(m_WidgetLayout);
    setContentsMargins(1.0, 1.0, 1.0, 1.0);
    widgetLayoutPolicy->setSpacing(5);

    // DownloadedLanguage
    /* LanguageLabelButtonContainer *downloadedCont =
        new LanguageLabelButtonContainer(LanguageLabelButtonContainer::DOWNLOADED,
                                         centralWidget);
    connect(downloadedCont, SIGNAL(removeMe(LanguageLabelButtonContainer*)),
            this, SLOT(removeContainer(LanguageLabelButtonContainer*)));*/
    
    // InstalledLanguage
    LanguageLabelButtonContainer *installedCont =
        new LanguageLabelButtonContainer(LanguageLabelButtonContainer::INSTALLED,
                                         centralWidget);
    connect(installedCont, SIGNAL(removeMe(LanguageLabelButtonContainer*)),
            this, SLOT(removeContainer(LanguageLabelButtonContainer*)));
    
    // LanguageSelectContainer
    LanguageSelectContainer *selectCont =
        new LanguageSelectContainer(DcpLanguage::InDeviceText,
                DcpLanguageConf::instance()->availableInputLanguages(), centralWidget);
    connect(selectCont, SIGNAL(changeBackToMain()), this, SLOT(accept()));

    // Add items to widgetLayoutPolicy
    // widgetLayoutPolicy->addItemAtPosition(downloadedCont, 0, Qt::AlignCenter);
    widgetLayoutPolicy->addItemAtPosition(installedCont, 0, Qt::AlignCenter);
    widgetLayoutPolicy->addItemAtPosition(selectCont, 1, Qt::AlignCenter);

    // setCentralWidget
    this->setCentralWidget(centralWidget);
}

void DisplayDialog::removeContainer(LanguageLabelButtonContainer *container)
{
    container->hide();
    int index = m_WidgetLayout->findIndexForItem(static_cast<QGraphicsItem*>(container));
    if (index != -1)
        m_WidgetLayout->removeAt(index);
}
