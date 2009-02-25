#include "hellowidget.h"

#include <duilinearlayout.h>
#include <duilabel.h>
#include <duislider.h>


HelloWidget::HelloWidget(QGraphicsWidget *parent)
	    :DuiWidget(parent)
{
	initWidget();
}


HelloWidget::~HelloWidget()
{
}


void HelloWidget::paint(QPainter *painter,
			const QStyleOptionGraphicsItem *option,
			QWidget *widget)
{
	Q_UNUSED(painter);
	Q_UNUSED(option);
	Q_UNUSED(widget);
}


void HelloWidget::initWidget()
{
	this->setMinimumWidth(DuiDeviceProfile::instance()->width());
	DuiLinearLayout *mainLayout = new DuiLinearLayout(Qt::Vertical, this);
	mainLayout->setPadding(10);
	
	DuiLabel *labelBrightness = new DuiLabel(QString("Brightness: %1 %").arg(40));
	labelBrightness->setObjectName("LabelBrightness");
	mainLayout->addItem(labelBrightness);
	
	DuiSlider *sliderBrightness = new DuiSlider(this);
	sliderBrightness->setOrientation(Qt::Horizontal);
	sliderBrightness->setRange(0, 100);
	sliderBrightness->setValue(50);
	sliderBrightness->setMaximumHeight(20);
	mainLayout->addItem(sliderBrightness);

	DuiLabel *labelScreen = new DuiLabel(QString("Screen lights on: %1 sec").arg(45));
	mainLayout->addItem(labelScreen);

	DuiSlider *sliderScreen = new DuiSlider(this);
	sliderScreen->setOrientation(Qt::Horizontal);
	sliderScreen->setRange(0, 100);
	sliderScreen->setValue(50);
	sliderScreen->setMaximumHeight(20);
	mainLayout->addItem(sliderScreen);

	DuiWidget *plainWidget = new DuiWidget(this);
	plainWidget->setMinimumHeight(7);
	plainWidget->setMaximumHeight(7);
	mainLayout->addItem(plainWidget);

	mainLayout->addItem(new DuiLabel("While charging keep screen lights"));
	
	DuiWidget *plainWidget2 = new DuiWidget(this);
	plainWidget2->setMinimumHeight(7);
	plainWidget2->setMaximumHeight(7);
	mainLayout->addItem(plainWidget2);

	mainLayout->addItem(new DuiLabel("Note! Display settings depend on the user power profile."));
}
