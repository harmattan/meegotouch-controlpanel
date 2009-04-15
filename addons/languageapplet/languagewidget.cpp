#include "languagewidget.h"
#include "languagebutton.h"
#include "servicescontainer.h"
#include "languagetranslation.h"

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
    
    /* QPen pen(QColor(120, 120, 120, 240));
    QBrush brush(QColor(20, 20, 20, 240));
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(QRectF(0.0, 0.0,
                            size().width(),
                            size().height()));*/
}

void LanguageWidget::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);

    m_displayButton->setMinimumWidth(size().width() - 20);
    m_keyboardButton->setMinimumWidth(size().width() - 20);
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

    ServicesContainer *servicesContainer = new ServicesContainer(this);

    DuiLabel *simpleText = new DuiLabel(DcpLanguage::SetLanguageText, 
                    this);
    simpleText->setObjectName("LanguageSimpleText");
    simpleText->setAlignment(Qt::AlignCenter);
    simpleText->setMaximumHeight(60);

    DuiButton *regionFormatButton = new DuiButton(DcpLanguage::RegionButtonTitle, this);
    regionFormatButton->setMaximumWidth(270);
    regionFormatButton->setMaximumHeight(60);
    regionFormatButton->setMinimumHeight(60);

    // SpacerItem
    DuiWidget *spacerItem = new DuiWidget(this);
    spacerItem->setMinimumHeight(20);
    spacerItem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // Layout
    DuiLayout *mainLayout = new DuiLayout(this);
    // mainLayout->setAnimator(0);
	DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    
    mainLayoutPolicy->setSpacing(15);
    mainLayoutPolicy->setContentsMargins(12.0, 20.0, 12.0, 20.0);

    // Add widgets
    mainLayoutPolicy->addItemAtPosition(m_displayButton, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_keyboardButton, 1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(servicesContainer, 2, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(simpleText, 3, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(regionFormatButton, 4, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(spacerItem, 5, Qt::AlignCenter);
}

void LanguageWidget::displayPage()
{
    m_Dlg = new DisplayDialog();
    this->setEnabled(false);
    m_Dlg->exec();
    this->setEnabled(true);
    m_Dlg->deleteLater();
}

void LanguageWidget::keyboardPage()
{
    m_Dlg = new KeyboardDialog();
    this->setEnabled(false);
    m_Dlg->exec();
    this->setEnabled(true);
    m_Dlg->deleteLater();
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
