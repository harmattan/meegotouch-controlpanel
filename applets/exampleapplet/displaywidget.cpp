#include "displaywidget.h"
#include "displaytranslation.h"
#include "dcpdisplay.h"
#include <DcpSpacerItem>
#include <duibutton.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duilabel.h>
#include <duislider.h>

const int widgetWidth = 100;

DisplayWidget::DisplayWidget(QGraphicsWidget *parent)
	    :DcpWidget(parent)
{
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

void DisplayWidget::onLocaleChanged()
{
    setScreenLabel(m_sliderScreen->value());
    setBrightnessLabel(m_sliderBrightness->value());
    m_screenLightLabel->setText(trid(DcpDisplay::chargingTextId,
                                     DcpDisplay::chargingTextDefault));
    m_noteText->setText(trid(DcpDisplay::noteTextId, DcpDisplay::noteTextDefault));
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
	m_brightnessLabel = new DuiLabel(this);
	m_brightnessLabel->setObjectName("LabelBrightness");
	
    // sliderBrightness
	m_sliderBrightness = new DuiSlider(this, "continuous");
	m_sliderBrightness->setOrientation(Qt::Horizontal);
	m_sliderBrightness->setRange(0, 100);
	m_sliderBrightness->setValue(50);
	m_sliderBrightness->setMaximumHeight(20);
	connect(m_sliderBrightness, SIGNAL(valueChanged(int )), 
		    this, SLOT(setBrightnessLabel(int)));

    // m_screenLabel
	m_screenLabel = new DuiLabel(this);
    m_screenLabel->setObjectName("LabelScreen");

    // sliderScreen
	m_sliderScreen = new DuiSlider(this, "continuous");
	m_sliderScreen->setOrientation(Qt::Horizontal);
	m_sliderScreen->setRange(0, 100);
	m_sliderScreen->setValue(50);
	m_sliderScreen->setMaximumHeight(20);
	connect(m_sliderScreen, SIGNAL(valueChanged(int )),
	 	    this, SLOT(setScreenLabel(int )));
	
    // screenHLayout
    DuiLayout *screenHLayout = new DuiLayout(0);
    screenHLayout->setAnimator(0);
    DuiLinearLayoutPolicy *screenHLayoutPolicy =
            new DuiLinearLayoutPolicy(screenHLayout, Qt::Horizontal);
    screenHLayout->setPolicy(screenHLayoutPolicy);
    screenHLayoutPolicy->setSpacing(20);

    // screenLightLabel
	DuiLabel *screenLightLabel = new DuiLabel(this);
    screenLightLabel->setObjectName("LabelScreenLight");

    // m_screenToggleButton
    m_screenToggleButton = new DuiButton(this);
    m_screenToggleButton->setObjectName("ScreenToggleButton");
    m_screenToggleButton->setMinimumSize(QSize(35, 35));
    m_screenToggleButton->setMaximumSize(QSize(35, 35));
    m_screenToggleButton->setCheckable(true);
    connect(m_screenToggleButton, SIGNAL(clicked()), this, SLOT(nextPage()));
    
    // Add items to screenHLayoutPolicy
	screenHLayoutPolicy->addItem(screenLightLabel, Qt::AlignLeft);
    screenHLayoutPolicy->addItem(m_screenToggleButton, Qt::AlignLeft);
    screenHLayoutPolicy->addItem(
                    new DcpSpacerItem(this, 20, 20, QSizePolicy::Expanding, 
                    QSizePolicy::Fixed), Qt::AlignLeft);

    // Add items to centralLayoutPolicy
	centralLayoutPolicy->addItem(m_brightnessLabel, Qt::AlignLeft);
	centralLayoutPolicy->addItem(m_sliderBrightness, Qt::AlignLeft);
	centralLayoutPolicy->addItem(m_screenLabel, Qt::AlignLeft);
	centralLayoutPolicy->addItem(m_sliderScreen, Qt::AlignLeft);
    centralLayoutPolicy->addItem(
                    new DcpSpacerItem(this, 10, 20, QSizePolicy::Expanding, 
                     QSizePolicy::Fixed), Qt::AlignCenter);
    centralLayoutPolicy->addItem(screenHLayout, Qt::AlignLeft);
	centralLayoutPolicy->addItem(
                    new DcpSpacerItem(this, 10, 10, QSizePolicy::Expanding, 
                    QSizePolicy::Fixed), Qt::AlignCenter);
    m_noteText = new DuiLabel(this);
    centralLayoutPolicy->addItem(m_noteText, Qt::AlignLeft);
    centralLayoutPolicy->addItem(
                    new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding,
                    QSizePolicy::Expanding), Qt::AlignCenter);

    // Add items to mainLayoutPolicy
    mainLayoutPolicy->addItem(
                    new DcpSpacerItem(this, widgetWidth, 10, QSizePolicy::Expanding, 
                    QSizePolicy::Expanding), Qt::AlignLeft);
    mainLayoutPolicy->addItem(centralLayout, Qt::AlignHCenter);
    mainLayoutPolicy->addItem(
                    new DcpSpacerItem(this, widgetWidth, 10, QSizePolicy::Expanding,
                    QSizePolicy::Expanding), Qt::AlignRight);

    this->setLayout(mainLayout);
    onLocaleChanged();
}

void DisplayWidget::setBrightnessLabel(int value)
{
	m_brightnessLabel->setText(trid(DcpDisplay::brightnessTextId,
                               DcpDisplay::brightnessTextDefault)
                    + QString(" %1 %").arg(value));
}

void DisplayWidget::setScreenLabel(int value)
{
	m_screenLabel->setText(trid(DcpDisplay::screenLightsTextId,
                                DcpDisplay::screenLightsTextDefault)
                    + QString(" %1 sec").arg(value));
}

void DisplayWidget::nextPage()
{
    // emit changeWidget(DcpDisplay::Page1);
}
