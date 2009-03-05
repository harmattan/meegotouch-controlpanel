#include "languagewidget.h"
#include "languagebutton.h"

#include <QPen>
#include <duigridlayout.h>
#include <duibutton.h>
#include <duilabel.h>


const int buttonHeight = 130;
const int buttonWidth  = 690;

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
	// Q_UNUSED(painter);
	Q_UNUSED(option);
	Q_UNUSED(widget);
    
    QPen pen(QColor(120, 120, 120, 255));
    QBrush brush(QColor(50, 50, 50, 255));
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(QRectF(0.0, 0.0,
                            size().width(),
                            size().height()));
}

void LanguageWidget::initWidget()
{
    // there is some "magic number" sorry for that
	this->setMinimumWidth(DuiDeviceProfile::instance()->width());
    this->setMinimumHeight(DuiDeviceProfile::instance()->height() - 40);
	DuiGridLayout *mainLayout = new DuiGridLayout(this);

    LanguageButton *firstButton = new LanguageButton("Display language",
                                                    "English", this);
    mainLayout->addItem(firstButton, 0, 0, Qt::AlignCenter);
    
    LanguageButton *secondButton = new LanguageButton("Keyboard (2)",
                                                    "English, Suomi", this);
    mainLayout->addItem(secondButton, 1, 0, Qt::AlignCenter);

    DuiLabel *simpleText = new DuiLabel("To set language display format, go to", 
                    this);
    simpleText->setAlignment(Qt::AlignCenter);
    simpleText->setMaximumHeight(60);
    mainLayout->addItem(simpleText, 2, 0, Qt::AlignCenter);

    DuiButton *regionFormatButton = new DuiButton("Region format", this);
    regionFormatButton->setMaximumWidth(350);
    regionFormatButton->setMaximumHeight(45);
    mainLayout->addItem(regionFormatButton, 3, 0, Qt::AlignCenter);

    firstButton->setMaximumHeight(buttonHeight);
    firstButton->setMinimumWidth(buttonWidth);
    secondButton->setMaximumHeight(buttonHeight);
    secondButton->setMinimumWidth(buttonWidth);
}
