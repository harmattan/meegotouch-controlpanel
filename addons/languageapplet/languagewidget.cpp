#include "languagewidget.h"
#include "languagetranslation.h"
#include "dcpbutton2.h"
#include "dcpspaceritem.h"
#include "dcplanguage.h"
#include "dcplanguageconf.h"
#include "displaydialog.h"
#include "keyboarddialog.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duibutton.h>
#include <duilabel.h>
#include <duiapplication.h>
#include <duiapplicationwindow.h>
#include <duinavigationbar.h>
#include <duiscenemanager.h>
#include <duiseparator.h>

#include <duiquerydialog.h>

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
    m_DisplayButton = new DcpButton2(this);
    m_DisplayButton->setText1(DcpLanguage::DisplayButtonTitle);
    m_DisplayButton->setText2(DcpLanguageConf::fullName(
                DcpLanguageConf::instance()->displayLanguage()));
    m_DisplayButton->setMinimumWidth(DuiSceneManager::instance()->visibleSceneSize().width()-24);
    m_DisplayButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(m_DisplayButton, SIGNAL(clicked()), this, SLOT(displayPage()));

    // m_KeyboardButton
    m_KeyboardButton = new DcpButton2(this);
    m_KeyboardButton->setText1(DcpLanguage::KeyboardButtonTitle + " (" +
        QString::number(DcpLanguageConf::instance()->keyboardLanguagesNumber())
        + ")");
    m_KeyboardButton->setText2(DcpLanguageConf::instance()->keyboardLanguagesAsText());
    m_KeyboardButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(m_KeyboardButton, SIGNAL(clicked()), this, SLOT(keyboardPage()));

    // simpleText
    DuiLabel *simpleText = new DuiLabel(DcpLanguage::SetLanguageText, 
                    this);
    simpleText->setObjectName("LanguageSimpleText");
    simpleText->setAlignment(Qt::AlignCenter);

    // regionFormatButton
    DuiButton *regionFormatButton = new DuiButton(DcpLanguage::RegionButtonTitle, this);
    regionFormatButton->setObjectName("RegionFormatButton");

    // separators
    DuiSeparator* separator1 = new DuiSeparator(this);
    DuiSeparator* separator2 = new DuiSeparator(this);

    // Layout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
	DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(0.0, 12.0, 0.0, 12.0);
    mainLayoutPolicy->setSpacing(0);

    // Add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(m_DisplayButton, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(separator1, 1);
    mainLayoutPolicy->addItemAtPosition(m_KeyboardButton, 2, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(separator2, 3);
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 30, QSizePolicy::Expanding, QSizePolicy::Fixed),
                    4, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(simpleText, 5, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(regionFormatButton, 6, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 
                    7, Qt::AlignCenter);
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
    m_Dlg = 0;
}

void LanguageWidget::keyboardPage()
{
    forever {
        // TODO: workaround for dui bug, please remove
        // ((DuiApplication*)DuiApplication::instance())->applicationWindow()->navigationBar()->showBackButton();

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
            DuiQueryDialog query(DcpLanguage::RestoreQueryLabelText);
            DuiButton* keepPreviousId = query.addButton(DcpLanguage::RestorePreviousText);
            query.addButton(DcpLanguage::SelectNewText);
            query.exec();
            if (query.clickedButton() == keepPreviousId)
                break;
        }
    }

    this->updateLanguageButtons();
    this->setEnabled(true);
    m_Dlg->deleteLater();
    m_Dlg=0;
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
   m_DisplayButton->setText1(DcpLanguage::DisplayButtonTitle);
   m_DisplayButton->setText2(DcpLanguageConf::fullName(
               DcpLanguageConf::instance()->displayLanguage()));

   m_KeyboardButton->setText1(DcpLanguage::KeyboardButtonTitle +
        " (" + QString::number(DcpLanguageConf::instance()->keyboardLanguagesNumber())
        + ")");
   m_KeyboardButton->setText2(DcpLanguageConf::instance()->keyboardLanguagesAsText());
}

