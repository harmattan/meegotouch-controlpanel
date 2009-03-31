#include "languagewidget.h"
#include "languagebutton.h"
#include "servicescontainer.h"

#include <QPen>
#include <duideviceprofile.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duibutton.h>
#include <duilabel.h>
#include <duitheme.h>
#include "dcpwidget.h"
#include "dcplanguage.h"

LanguageWidget::LanguageWidget(QGraphicsWidget *parent)
	    :DcpWidget(parent)
{
	initWidget();
}

LanguageWidget::~LanguageWidget()
{
}

void LanguageWidget::paint(QPainter *painter,
			               const QStyleOptionGraphicsItem *option,
			               QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
    
    QPen pen(QColor(120, 120, 120, 240));
    QBrush brush(QColor(20, 20, 20, 240));
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(QRectF(0.0, 0.0,
                            size().width(),
                            size().height()));
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
    m_displayButton = new LanguageButton("Display language",
                                       "English GB", this);
    m_displayButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(m_displayButton, SIGNAL(clicked()), 
            this, SLOT(displayPage()));
    
    m_keyboardButton = new LanguageButton("Keyboard languages (2)",
                                                    "English GB, Suomi", this);
    m_keyboardButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(m_keyboardButton, SIGNAL(clicked()),
            this, SLOT(keyboardPage()));

    ServicesContainer *servicesContainer = new ServicesContainer(this);

    DuiLabel *simpleText = new DuiLabel("To set language display format, go to", 
                    this);
    simpleText->setObjectName("LanguageSimpleText");
    simpleText->setAlignment(Qt::AlignCenter);
    simpleText->setMaximumHeight(60);

    DuiButton *regionFormatButton = new DuiButton("Region format", this);
    regionFormatButton->setMaximumWidth(270);
    regionFormatButton->setMaximumHeight(60);
    regionFormatButton->setMinimumHeight(60);

    // Layout
    DuiLayout *mainLayout = new DuiLayout(this);
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
}

void LanguageWidget::displayPage()
{
    emit changeWidget(DcpLanguage::Display);
}

void LanguageWidget::keyboardPage()
{
    emit changeWidget(DcpLanguage::Keyboard);
}
