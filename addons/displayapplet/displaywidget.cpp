#include "displaywidget.h"
#include "displaytranslation.h"
#include "dcpdisplay.h"
#include "dcpspaceritem.h"
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
    mainLayout->setAnimator(0);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Horizontal);
    mainLayout->setPolicy(mainLayoutPolicy);
	
    // centralLayout
    DuiLayout *centralLayout = new DuiLayout(0);
    centralLayout->setAnimator(0);
    DuiLinearLayoutPolicy *centralLayoutPolicy =
            new DuiLinearLayoutPolicy(centralLayout, Qt::Vertical);
    centralLayout->setPolicy(centralLayoutPolicy);
    centralLayoutPolicy->setContentsMargins(5.0, 20.0, 5.0, 20.0);
    centralLayoutPolicy->setSpacing(20);
	
    // m_brightnessLabel
	m_brightnessLabel = new DuiLabel(DcpDisplay::BrightnessText 
                    + QString(" %1 %").arg(50), this);
	m_brightnessLabel->setObjectName("LabelBrightness");
	
    // sliderBrightness
	DuiSlider *sliderBrightness = new DuiSlider(this, "continuous");
	sliderBrightness->setOrientation(Qt::Horizontal);
	sliderBrightness->setRange(0, 100);
	sliderBrightness->setValue(50);
	sliderBrightness->setMaximumHeight(20);
	connect(sliderBrightness, SIGNAL(valueChanged(int )), 
		    this, SLOT(setBrightnessLabel(int)));

    // m_screenLabel
	m_screenLabel = new DuiLabel(DcpDisplay::ScreenLightsText 
                    + QString(" %1 sec").arg(50), this);
    m_screenLabel->setObjectName("LabelScreen");

    // sliderScreen
	DuiSlider *sliderScreen = new DuiSlider(this, "continuous");
	sliderScreen->setOrientation(Qt::Horizontal);
	sliderScreen->setRange(0, 100);
	sliderScreen->setValue(50);
	sliderScreen->setMaximumHeight(20);
	connect(sliderScreen, SIGNAL(valueChanged(int )),
	 	    this, SLOT(setScreenLabel(int )));
	
    // screenHLayout
    DuiLayout *screenHLayout = new DuiLayout(0);
    screenHLayout->setAnimator(0);
    DuiLinearLayoutPolicy *screenHLayoutPolicy =
            new DuiLinearLayoutPolicy(screenHLayout, Qt::Horizontal);
    screenHLayout->setPolicy(screenHLayoutPolicy);
    screenHLayoutPolicy->setSpacing(20);

    // screenLightLabel
	DuiLabel *screenLightLabel = new DuiLabel(DcpDisplay::ChargingText, this);
    screenLightLabel->setObjectName("LabelScreenLight");

    // m_screenToggleButton
    m_screenToggleButton = new DuiButton(this);
    m_screenToggleButton->setObjectName("ScreenToggleButton");
    m_screenToggleButton->setMinimumSize(QSize(35, 35));
    m_screenToggleButton->setMaximumSize(QSize(35, 35));
    m_screenToggleButton->setCheckable(true);
    connect(m_screenToggleButton, SIGNAL(clicked()), this, SLOT(nextPage()));
    
    // Add items to screenHLayoutPolicy
	screenHLayoutPolicy->addItemAtPosition(screenLightLabel, 0, Qt::AlignLeft);
    screenHLayoutPolicy->addItemAtPosition(m_screenToggleButton, 1, Qt::AlignLeft);
    screenHLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 20, 20, QSizePolicy::Expanding, 
                    QSizePolicy::Fixed), 2, Qt::AlignLeft);

    // Add items to centralLayoutPolicy
	centralLayoutPolicy->addItemAtPosition(m_brightnessLabel, 0, Qt::AlignLeft);
	centralLayoutPolicy->addItemAtPosition(sliderBrightness, 1, Qt::AlignLeft);
	centralLayoutPolicy->addItemAtPosition(m_screenLabel, 2, Qt::AlignLeft);
	centralLayoutPolicy->addItemAtPosition(sliderScreen, 3, Qt::AlignLeft);
    centralLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 20, QSizePolicy::Expanding, 
                     QSizePolicy::Fixed), 4, Qt::AlignCenter);
    centralLayoutPolicy->addItemAtPosition(screenHLayout, 5, Qt::AlignLeft);
	centralLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 10, QSizePolicy::Expanding, 
                    QSizePolicy::Fixed), 6, Qt::AlignCenter);
	centralLayoutPolicy->addItemAtPosition(new DuiLabel(DcpDisplay::NoteText, this),
                                           7, Qt::AlignLeft);
    centralLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding,
                    QSizePolicy::Expanding), 8, Qt::AlignCenter);

    // Add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, widgetWidth, 10, QSizePolicy::Expanding, 
                    QSizePolicy::Expanding), 0, Qt::AlignLeft);
    mainLayoutPolicy->addItemAtPosition(centralLayout, 1, Qt::AlignHCenter);
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, widgetWidth, 10, QSizePolicy::Expanding,
                    QSizePolicy::Expanding), 2, Qt::AlignRight);

    this->setLayout(mainLayout);
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
    // emit changeWidget(DcpDisplay::Page1);
}
