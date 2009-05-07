#include "keyboarddialog.h"
#include "keyboardselectcontainer.h"
#include "languagelabelbuttoncontainer.h"
#include "languagetranslation.h"
#include "dcplanguage.h"
#include "dcplanguageconf.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>

#ifdef QUERY_DIALOG
    #include <duiquerydialog.h>
#else
    #include <DuiMessageBox>
#endif

KeyboardDialog::KeyboardDialog()
              :CommonDialog(DcpLanguage::SelectKeyboardText)
{
    initWidget();
}

KeyboardDialog::~KeyboardDialog()
{
}

void KeyboardDialog::initWidget()
{
    m_OldLanguages = DcpLanguageConf::instance()->keyboardLanguages();

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

    // KeyboardSelectContainer
    KeyboardSelectContainer *selectCont =
        new KeyboardSelectContainer(DcpLanguage::InDeviceText,
                DcpLanguageConf::instance()->availableKeyboardLanguages(), centralWidget);

    // Add items to widgetLayoutPolicy
    // widgetLayoutPolicy->addItemAtPosition(downloadedCont, 0, Qt::AlignCenter);
    widgetLayoutPolicy->addItemAtPosition(installedCont, 0, Qt::AlignCenter);
    widgetLayoutPolicy->addItemAtPosition(selectCont, 1, Qt::AlignCenter);

    // setCentralWidget
    this->setCentralWidget(centralWidget);
}

#ifdef QUERY_DIALOG
void KeyboardDialog::close()
{
    DcpDialog::close();
    if (!DcpLanguageConf::instance()->keyboardLanguagesNumber()) {
            DuiQueryDialog query("You have not selected any keyboard language,<br>"
                                 "would you like to keep the previous selection?");
            DuiButton* keepPrevious = query.addButton("Keep previous");
            query.addButton("Select new");
            query.exec();
            if (query.clickedButton() == keepPrevious)
            {
                qDebug("DCP: accepted");
                DcpLanguageConf::instance()->setKeyboardLanguages(m_OldLanguages);
            } else {
		        emit reopen();
	        }
    }
}
#else
void KeyboardDialog::close()
{
    if (!DcpLanguageConf::instance()->keyboardLanguagesNumber()) {
        DuiMessageBox mb("Keep last selection of languages?",
                         DuiMessageBox::Ok|DuiMessageBox::Cancel);
        int result = mb.exec();
        qDebug() << "DCP: result is" << result;
        if (result == 1) { //DuiDialog::Accepted is wrong!!!
            qDebug("DCP: accepted");
            DcpLanguageConf::instance()->setKeyboardLanguages(m_OldLanguages);
            DcpDialog::close();
        } else {
            mb.disappear();  
            return; 
        }
    }

    DcpDialog::close();
}
#endif

void KeyboardDialog::removeContainer(LanguageLabelButtonContainer *container)
{
    container->hide();
    int index = m_WidgetLayout->findIndexForItem(static_cast<QGraphicsItem*>(container));
    if (index != -1)
        m_WidgetLayout->removeAt(index);
}

