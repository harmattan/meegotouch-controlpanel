#include "displaywidget.h"
#include "displaytranslation.h"
#include "dcpdisplay.h"
#include <duitheme.h>
#include <duibutton.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duilabel.h>
#include <duislider.h>

const QString cssDir = "/usr/share/themes/dui/duicontrolpanel/";
const int widgetWidth = 100;

DisplayWidget::DisplayWidget(QGraphicsWidget *parent)
	    :DcpWidget(parent)
{
    DuiTheme::loadCSS(cssDir + "displayapplet.css");
    setReferer(DcpDisplay::NoReferer);
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
    DuiLayout *mainLayout = new DuiLayout(this);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Horizontal);
    mainLayout->setPolicy(mainLayoutPolicy);
	
    // leftWidget
    DuiWidget *leftWidget  = new DuiWidget(this);
    leftWidget->setMinimumWidth(widgetWidth);
    leftWidget->setMaximumWidth(widgetWidth);
    leftWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    // centralLayout
    DuiLayout *centralLayout = new DuiLayout(0);
    DuiLinearLayoutPolicy *centralLayoutPolicy =
            new DuiLinearLayoutPolicy(centralLayout, Qt::Vertical);
    centralLayout->setPolicy(centralLayoutPolicy);
    centralLayoutPolicy->setContentsMargins(5.0, 20.0, 5.0, 20.0);
	
	m_brightnessLabel = new DuiLabel(DcpDisplay::BrightnessText 
                    + QString(" %1 %").arg(50));
	m_brightnessLabel->setObjectName("LabelBrightness");
	centralLayoutPolicy->addItemAtPosition(m_brightnessLabel, 0, Qt::AlignLeft);
	
	DuiSlider *sliderBrightness = new DuiSlider(this, "continuous");
	sliderBrightness->setOrientation(Qt::Horizontal);
	sliderBrightness->setRange(0, 100);
	sliderBrightness->setValue(50);
	sliderBrightness->setMaximumHeight(20);
	connect(sliderBrightness, SIGNAL(valueChanged(int )), 
		this, SLOT(setBrightnessLabel(int)));
	centralLayoutPolicy->addItemAtPosition(sliderBrightness, 1, Qt::AlignLeft);

	m_screenLabel = new DuiLabel(DcpDisplay::ScreenLightsText 
                    + QString(" %1 sec").arg(50));
    m_screenLabel->setObjectName("LabelScreen");
	centralLayoutPolicy->addItemAtPosition(m_screenLabel, 2, Qt::AlignLeft);

	DuiSlider *sliderScreen = new DuiSlider(this, "continuous");
	sliderScreen->setOrientation(Qt::Horizontal);
	sliderScreen->setRange(0, 100);
	sliderScreen->setValue(50);
	sliderScreen->setMaximumHeight(20);
	connect(sliderScreen, SIGNAL(valueChanged(int )),
	 	this, SLOT(setScreenLabel(int )));
	centralLayoutPolicy->addItemAtPosition(sliderScreen, 3, Qt::AlignLeft);

	DuiWidget *spacerItem = new DuiWidget(this);
	spacerItem->setMinimumHeight(40);
	spacerItem->setMaximumHeight(40);
	centralLayoutPolicy->addItemAtPosition(spacerItem, 4, Qt::AlignCenter);

    // screenHLayout
    DuiLayout *screenHLayout = new DuiLayout(0);
    DuiLinearLayoutPolicy *screenHLayoutPolicy =
            new DuiLinearLayoutPolicy(screenHLayout, Qt::Horizontal);
    screenHLayout->setPolicy(screenHLayoutPolicy);
    screenHLayoutPolicy->setSpacing(20);

	DuiLabel *screenLightLabel = new DuiLabel(DcpDisplay::ChargingText, this);
    screenLightLabel->setObjectName("LabelScreenLight");
	screenHLayoutPolicy->addItemAtPosition(screenLightLabel, 0, Qt::AlignLeft);

    m_screenToggleButton = new DuiButton(this);
    m_screenToggleButton->setObjectName("ScreenToggleButton");
    m_screenToggleButton->setCheckable(true);
    // connect(m_screenToggleButton, SIGNAL(clicked()), this, SLOT(nextPage()));
    screenHLayoutPolicy->addItemAtPosition(m_screenToggleButton, 1, Qt::AlignLeft);

    DuiWidget *spacerItem2 = new DuiWidget(this);
    spacerItem2->setMaximumHeight(20);
    spacerItem2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    screenHLayoutPolicy->addItemAtPosition(spacerItem2, 2, Qt::AlignLeft);

    centralLayoutPolicy->addItemAtPosition(screenHLayout, 5, Qt::AlignLeft);
    
	DuiWidget *spacerItem3 = new DuiWidget(this);
	spacerItem3->setMinimumHeight(30);
	spacerItem3->setMaximumHeight(30);
	centralLayoutPolicy->addItemAtPosition(spacerItem3, 6, Qt::AlignCenter);

	centralLayoutPolicy->addItemAtPosition(
                    new DuiLabel(DcpDisplay::NoteText),
                    7, Qt::AlignLeft);

    DuiWidget *spacerItem4 = new DuiWidget(this);
    spacerItem4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    centralLayoutPolicy->addItemAtPosition(spacerItem4, 8, Qt::AlignCenter);

    // rigthWidget
    DuiWidget *rightWidget  = new DuiWidget(this);
    rightWidget->setMinimumWidth(widgetWidth);
    rightWidget->setMaximumWidth(widgetWidth);
    rightWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    mainLayoutPolicy->addItemAtPosition(leftWidget, 0, Qt::AlignLeft);
    mainLayoutPolicy->addItemAtPosition(centralLayout, 1, Qt::AlignHCenter);
    mainLayoutPolicy->addItemAtPosition(rightWidget, 2, Qt::AlignRight);

}

void DisplayWidget::setBrightnessLabel(int value)
{
	m_brightnessLabel->setText(DcpDisplay::BrightnessText 
                    + QString(" %1 %").arg(value));
}

void DisplayWidget::setScreenLabel(int value)
{
	m_screenLabel->setText(DcpDisplay::ScreenLightsText 
                    + QString(" %1 sec").arg(value));
}

void DisplayWidget::nextPage()
{
    emit changeWidget(DcpDisplay::Page1);
}
