#include "languagewidget.h"
#include "languagebutton.h"
#include "servicescontainer.h"
#include "languagetranslation.h"
#include "dcpspaceritem.h"

#include <QPen>
#include <duideviceprofile.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duibutton.h>
#include <duilabel.h>
#include <duitheme.h>
#include "dcpwidget.h"
#include "dcplanguage.h"
#include "dcplanguageconf.h"
#include "displaydialog.h"
#include "keyboarddialog.h"

LanguageWidget::LanguageWidget(QGraphicsWidget *parent)
	    :DcpWidget(parent), m_Dlg(0)
{
    setReferer(DcpLanguage::NoReferer);
	initWidget();
}

LanguageWidget::~LanguageWidget()
{
}

void LanguageWidget::paint(QPainter *painter,
			               const QStyleOptionGraphicsItem *option,
			               QWidget *widget)
{
    Q_UNUSED(painter);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}

void LanguageWidget::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);

    m_displayButton->setMinimumWidth(size().width());
    m_keyboardButton->setMinimumWidth(size().width());
}

void LanguageWidget::initWidget()
{
    // there is some "magic number" sorry for that
    m_displayButton = new LanguageButton(DcpLanguage::DisplayButtonTitle,
                            DcpLanguageConf::instance()->displayLanguage(), this);
    m_displayButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(m_displayButton, SIGNAL(clicked()), 
            this, SLOT(displayPage()));
    
    m_keyboardButton = new LanguageButton(DcpLanguage::KeyboardButtonTitle + 
    " (" +  QString::number(DcpLanguageConf::instance()->keyboardLanguagesNumber())
     + ")",
              DcpLanguageConf::instance()->keyboardLanguagesAsText(), this);
    m_keyboardButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(m_keyboardButton, SIGNAL(clicked()),
            this, SLOT(keyboardPage()));

    // ServicesContainer *servicesContainer = new ServicesContainer(this);

    DuiLabel *simpleText = new DuiLabel(DcpLanguage::SetLanguageText, 
                    this);
    simpleText->setObjectName("LanguageSimpleText");
    simpleText->setAlignment(Qt::AlignCenter);
    simpleText->setMaximumHeight(60);

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
    
    mainLayoutPolicy->setSpacing(15);

    // Add widgets
    mainLayoutPolicy->addItemAtPosition(m_displayButton, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_keyboardButton, 1, Qt::AlignCenter);
    // mainLayoutPolicy->addItemAtPosition(servicesContainer, 2, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 30, QSizePolicy::Expanding, QSizePolicy::Fixed),
                    2, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(simpleText, 3, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(regionFormatButton, 4, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 
                    5, Qt::AlignCenter);
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
    m_Dlg = new KeyboardDialog();
    this->setEnabled(false);
    m_Dlg->exec();
    this->updateLanguageButtons();
    this->setEnabled(true);
    m_Dlg->deleteLater();
    m_Dlg=NULL;
}

bool LanguageWidget::back()
{
    if (m_Dlg)
        {
            m_Dlg->done(0);
            return false;
        }
    return DcpWidget::back();
}

void LanguageWidget::updateLanguageButtons()
{
   m_displayButton->setDownText(DcpLanguageConf::instance()->displayLanguage());
   m_keyboardButton->setUpText(DcpLanguage::KeyboardButtonTitle +
                               " (" +  
                               QString::number(DcpLanguageConf::instance()->keyboardLanguagesNumber())
                                + ")");
   m_keyboardButton->setDownText(DcpLanguageConf::instance()->keyboardLanguagesAsText());
}
