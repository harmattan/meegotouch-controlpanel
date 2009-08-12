#include "languagewidget.h"
#include "languagetranslation.h"
#include "dcpbutton2.h"
#include "dcpspaceritem.h"
#include "dcplanguage.h"
#include "dcplanguageconf.h"
#include "displaydialog.h"
#include "keyboarddialog.h"

#include <duibutton.h>
#include <duilabel.h>
#include <duiapplication.h>
#include <duiapplicationwindow.h>
#include <duinavigationbar.h>
#include <duiscenemanager.h>
#include <duiseparator.h>
#include <duiquerydialog.h>
#include <QGraphicsLinearLayout>

static const QString separatorObjectName = "DcpSmallSeparator";

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

    // separators:
    DuiSeparator* sep1 = new DuiSeparator(this);
    sep1->setObjectName(separatorObjectName);
    DuiSeparator* sep2 = new DuiSeparator(this);
    sep2->setObjectName(separatorObjectName);

    // Layout
    QGraphicsLinearLayout *mainLayout = new QGraphicsLinearLayout(Qt::Vertical, this);
    mainLayout->setContentsMargins(0.0, 12.0, 0.0, 12.0);
    mainLayout->setSpacing(0);

    // Add items to mainLayoutPolicy
    mainLayout->addItem(m_DisplayButton);
    mainLayout->addItem(sep1);
    mainLayout->addItem(m_KeyboardButton);
    mainLayout->addItem(sep2);
    mainLayout->addItem(new DcpSpacerItem(this, 10, 30, QSizePolicy::Expanding, QSizePolicy::Fixed));
    mainLayout->addItem(simpleText);
    mainLayout->setAlignment(simpleText, Qt::AlignCenter);
    mainLayout->addItem(regionFormatButton);
    mainLayout->setAlignment(regionFormatButton, Qt::AlignCenter);
    mainLayout->addItem(new DcpSpacerItem(this, 10, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
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

