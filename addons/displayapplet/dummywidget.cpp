#include "dummywidget.h"
#include "dcpdisplay.h"

#include <duitheme.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duilabel.h>
#include <duibutton.h>
const QString cssDir = "/usr/share/themes/dui/duicontrolpanel/";
const int widgetWidth = 100;

DummyWidget::DummyWidget(const QString& text, QGraphicsWidget *parent)
	    :DcpWidget(parent)
{
    DuiTheme::loadCSS(cssDir + "displayapplet.css");
	m_Label = new DuiLabel(text, this);
    initWidget();
    setReferer(DcpDisplay::Main);
}

DummyWidget::~DummyWidget()
{
}

void DummyWidget::paint(QPainter *painter,
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

void DummyWidget::initWidget()
{
    DuiLayout *mainLayout = new DuiLayout(this);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->addItemAtPosition(m_Label, 0, Qt::AlignCenter);
    this->setLayout(mainLayout);
}
