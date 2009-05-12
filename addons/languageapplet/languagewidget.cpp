#include "languagewidget.h"
#include "languagebutton.h"
#include "languagetranslation.h"
#include "dcpspaceritem.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duibutton.h>
#include <duilabel.h>
#include <duiapplication.h>
#include <duiapplicationwindow.h>
#include <duinavigationbar.h>
#include "dcplanguage.h"
#include "dcplanguageconf.h"
#include "displaydialog.h"
#include "keyboarddialog.h"

#ifdef QUERY_DIALOG
    #include <DuiQueryDialog>
#else
    #include <DuiMessageBox>
#endif

LanguageWidget::LanguageWidget(QGraphicsWidget *parent)
	    :DcpWidget(parent), m_Dlg(0)
{
    setReferer(DcpLanguage::NoReferer);
	initWidget();
}

LanguageWidget::~LanguageWidget()
{
}

void LanguageWidget::initWidget()
{
    // m_DisplayButton
    m_DisplayButton = new LanguageButton(DcpLanguage::DisplayButtonTitle,
    DcpLanguageConf::fullName(DcpLanguageConf::instance()->displayLanguage()),
     this);
    m_DisplayButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(m_DisplayButton, SIGNAL(clicked()), this, SLOT(displayPage()));

    // m_KeyboardButton
    m_KeyboardButton = new LanguageButton(DcpLanguage::KeyboardButtonTitle + 
    " (" +  QString::number(DcpLanguageConf::instance()->keyboardLanguagesNumber())
     + ")",
              DcpLanguageConf::instance()->keyboardLanguagesAsText(), this);
    m_KeyboardButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(m_KeyboardButton, SIGNAL(clicked()), this, SLOT(keyboardPage()));

    // ServicesContainer *servicesContainer = new ServicesContainer(this);

    // simpleText
    DuiLabel *simpleText = new DuiLabel(DcpLanguage::SetLanguageText, 
                    this);
    simpleText->setObjectName("LanguageSimpleText");
    simpleText->setAlignment(Qt::AlignCenter);
    simpleText->setMaximumHeight(60);

    // regionFormatButton
    DuiButton *regionFormatButton = new DuiButton(DcpLanguage::RegionButtonTitle, this);
    regionFormatButton->setObjectName("RegionFormatButton");
    regionFormatButton->setMaximumWidth(380);
    regionFormatButton->setMaximumHeight(60);
    regionFormatButton->setMinimumHeight(60);

    // Layout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(NULL);
	DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(0.0, 12.0, 0.0, 12.0);
    mainLayoutPolicy->setSpacing(15);

    // Add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(m_DisplayButton, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_KeyboardButton, 1, Qt::AlignCenter);
    // mainLayoutPolicy->addItemAtPosition(servicesContainer, 2, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 30, QSizePolicy::Expanding, QSizePolicy::Fixed),
                    2, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(simpleText, 3, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(regionFormatButton, 4, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 
                    5, Qt::AlignCenter);
    this->setLayout(mainLayout);
}

void LanguageWidget::displayPage()
{
    m_Dlg = new DisplayDialog();
    this->setEnabled(false);
    m_Dlg->exec();
    this->updateLanguageButtons();
    this->setEnabled(true);
    m_Dlg->deleteLater();
    m_Dlg=NULL;
}

void LanguageWidget::keyboardPage()
{
    forever {
        // TODO: workaround for dui bug, please remove
        ((DuiApplication*)DuiApplication::instance())->applicationWindow()->navigationBar()->showBackButton();

        m_Dlg = new KeyboardDialog();
        this->setEnabled(false);
        m_Dlg->exec();

        QStringList selectedLanguages = 
            ((KeyboardDialog*)(m_Dlg))->selectedLanguages();
        if (selectedLanguages.count() > 0) {
            // update the keyboard languages:
            DcpLanguageConf::instance()->setKeyboardLanguages (selectedLanguages);
            break;

        } else {
            // user selected no languages:
#ifdef QUERY_DIALOG
            DuiQueryDialog query(DcpLanguage::RestoreQueryLabelText);
            int keepPreviousId = query.addChoice(DcpLanguage::RestorePreviousText);
            query.addChoice(DcpLanguage::SelectNewText);
            query.exec();
            if (query.acceptedChoice() == keepPreviousId)
                break;
#else
            DuiMessageBox mb(DcpLanguage::RestoreQueryLabelText,
                             DuiMessageBoxModel::Ok|DuiMessageBoxModel::Cancel);
            int result = mb.exec();
            mb.disappear();
            if (result == 1) { //DuiDialog::Accepted is wrong!!!
                break;
            }
#endif
        }
    }

    this->updateLanguageButtons();
    this->setEnabled(true);
    m_Dlg->deleteLater();
    m_Dlg=NULL;
}

bool LanguageWidget::back()
{
    if (m_Dlg) {
        m_Dlg->close();
        return false;
    }

    return DcpWidget::back();
}

void LanguageWidget::updateLanguageButtons()
{
   m_DisplayButton->setDownText(
        DcpLanguageConf::fullName(DcpLanguageConf::instance()->displayLanguage()));
   m_KeyboardButton->setUpText(DcpLanguage::KeyboardButtonTitle +
                               " (" +
                               QString::number(DcpLanguageConf::instance()->keyboardLanguagesNumber())
                                + ")");
   m_KeyboardButton->setDownText(DcpLanguageConf::instance()->keyboardLanguagesAsText());
}

