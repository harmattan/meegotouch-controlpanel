#include "displaywidget.h"

#include <duitheme.h>
#include <duibutton.h>
#include <duilinearlayout.h>
#include <duilabel.h>
#include <duislider.h>

const QString cssDir = "/usr/share/themes/dui/duicontrolpanel/";
const int widgetWidth = 100;

DisplayWidget::DisplayWidget(QGraphicsWidget *parent)
	    :DcpWidget(parent)
{
    DuiTheme::loadCSS(cssDir + "displayapplet.css");
	initWidget();
}

DisplayWidget::~DisplayWidget()
{
}

void DisplayWidget::paint(QPainter *painter,
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

void DisplayWidget::initWidget()
{
    DuiLinearLayout *mainLayout = new DuiLinearLayout(Qt::Horizontal, this);
	
    // leftWidget
    DuiWidget *leftWidget  = new DuiWidget(this);
    leftWidget->setMinimumWidth(widgetWidth);
    leftWidget->setMaximumWidth(widgetWidth);
    leftWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    // centralLayout
    DuiLinearLayout *centralLayout = new DuiLinearLayout(Qt::Vertical, 0);
	
	m_brightnessLabel = new DuiLabel(QString("Brightness: %1 %").arg(0));
	m_brightnessLabel->setObjectName("LabelBrightness");
	centralLayout->addItem(m_brightnessLabel);
	
	DuiSlider *sliderBrightness = new DuiSlider(this);
	sliderBrightness->setOrientation(Qt::Horizontal);
	sliderBrightness->setRange(0, 100);
	sliderBrightness->setValue(50);
	sliderBrightness->setMaximumHeight(20);
	connect(sliderBrightness, SIGNAL(valueChanged(int )), 
		this, SLOT(setBrightnessLabel(int)));
	centralLayout->addItem(sliderBrightness);

	m_screenLabel = new DuiLabel(QString("Screen lights on: %1 sec").arg(0));
    m_screenLabel->setObjectName("LabelScreen");
	centralLayout->addItem(m_screenLabel);

	DuiSlider *sliderScreen = new DuiSlider(this);
	sliderScreen->setOrientation(Qt::Horizontal);
	sliderScreen->setRange(0, 100);
	sliderScreen->setValue(50);
	sliderScreen->setMaximumHeight(20);
	connect(sliderScreen, SIGNAL(valueChanged(int )),
	 	this, SLOT(setScreenLabel(int )));
	centralLayout->addItem(sliderScreen);

	DuiWidget *spacerItem = new DuiWidget(this);
	spacerItem->setMinimumHeight(40);
	spacerItem->setMaximumHeight(40);
	centralLayout->addItem(spacerItem);

    // screenHLayout
    DuiLinearLayout *screenHLayout = new DuiLinearLayout(Qt::Horizontal, 0);
    screenHLayout->setSpacing(20);

	DuiLabel *screenLightLabel = new DuiLabel("While charging keep screen lights", this);
    screenLightLabel->setObjectName("LabelScreenLight");
	screenHLayout->addItem(screenLightLabel);

    m_screenToggleButton = new DuiButton(this);
    m_screenToggleButton->setObjectName("ScreenToggleButton");
    m_screenToggleButton->setCheckable(true);
    screenHLayout->addItem(m_screenToggleButton);

    DuiWidget *spacerItem2 = new DuiWidget(this);
    spacerItem2->setMaximumHeight(20);
    spacerItem2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    screenHLayout->addItem(spacerItem2);

    screenHLayout->setAlignment(screenLightLabel, Qt::AlignLeft | Qt::AlignVCenter);
    screenHLayout->setAlignment(m_screenToggleButton, Qt::AlignLeft | Qt::AlignVCenter);

    centralLayout->addItem(screenHLayout);
    
	DuiWidget *spacerItem3 = new DuiWidget(this);
	spacerItem3->setMinimumHeight(30);
	spacerItem3->setMaximumHeight(30);
	centralLayout->addItem(spacerItem3);

	centralLayout->addItem(new DuiLabel("Note! Display settings depend on the user power profile."));

    DuiWidget *spacerItem4 = new DuiWidget(this);
    spacerItem4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    centralLayout->addItem(spacerItem4);

    centralLayout->setAlignment(m_brightnessLabel, Qt::AlignLeft | Qt::AlignVCenter);

    // rigthWidget
    DuiWidget *rightWidget  = new DuiWidget(this);
    rightWidget->setMinimumWidth(widgetWidth);
    rightWidget->setMaximumWidth(widgetWidth);
    rightWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    mainLayout->addItem(leftWidget);
    mainLayout->addItem(centralLayout);
    mainLayout->addItem(rightWidget);

    mainLayout->setAlignment(leftWidget, Qt::AlignLeft);
    mainLayout->setAlignment(centralLayout, Qt::AlignHCenter);
    mainLayout->setAlignment(rightWidget, Qt::AlignRight);
}

void DisplayWidget::setBrightnessLabel(int value)
{
	m_brightnessLabel->setText(QString("Brightness: %1 %").arg(value));
}

void DisplayWidget::setScreenLabel(int value)
{
	m_screenLabel->setText(QString("Screen lights on: %1 sec").arg(value));
}
