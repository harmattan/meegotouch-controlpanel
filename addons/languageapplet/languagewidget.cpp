#include "languagewidget.h"
#include "languagebutton.h"
#include "servicescontainer.h"

#include <QPen>
#include <duideviceprofile.h>
#include <duilinearlayout.h>
#include <duibutton.h>
#include <duilabel.h>
#include <duitheme.h>


LanguageWidget::LanguageWidget(QGraphicsWidget *parent)
	    :DuiWidget(parent)
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
	DuiLinearLayout *mainLayout = new DuiLinearLayout(Qt::Vertical, this);
    mainLayout->setSpacing(15);

    m_displayButton = new LanguageButton("Display language",
                                       "English GB", this);
    mainLayout->addItem(m_displayButton);
    
    m_keyboardButton = new LanguageButton("Keyboard languages (2)",
                                                    "English GB, Suomi", this);
    mainLayout->addItem(m_keyboardButton);

    ServicesContainer *servicesContainer = new ServicesContainer(this);
    mainLayout->addItem(servicesContainer);

    DuiLabel *simpleText = new DuiLabel("To set language display format, go to", 
                    this);
    simpleText->setObjectName("LanguageSimpleText");
    simpleText->setAlignment(Qt::AlignCenter);
    simpleText->setMaximumHeight(60);
    mainLayout->addItem(simpleText);

    DuiButton *regionFormatButton = new DuiButton("Region format", this);
    regionFormatButton->setMaximumWidth(320);
    regionFormatButton->setMaximumHeight(65);
    mainLayout->addItem(regionFormatButton);

    mainLayout->setAlignment(m_displayButton, Qt::AlignCenter);
    mainLayout->setAlignment(m_keyboardButton, Qt::AlignCenter);
    mainLayout->setAlignment(servicesContainer, Qt::AlignCenter);
    mainLayout->setAlignment(simpleText, Qt::AlignCenter);
    mainLayout->setAlignment(regionFormatButton, Qt::AlignCenter);
}
