#include "hellowidget.h"

#include <duilinearlayout.h>
#include <duilabel.h>


HelloWidget::HelloWidget(QGraphicsWidget *parent)
	    :DuiWidget(parent),
	     m_minimumSize(QSize(300, 300)),
	     m_preferredSize(QSize(300, 300)),
	     m_maximumSize(QSize(300, 300))
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


QSizeF HelloWidget::minimumSize() const
{
	return m_minimumSize;
}


QSizeF HelloWidget::preferredSize() const
{
	return m_preferredSize;
}


QSizeF HelloWidget::maximumSize() const
{
	return m_maximumSize;
}


void HelloWidget::initWidget()
{
	DuiLinearLayout *mainLayout = new DuiLinearLayout(Qt::Horizontal, this);
	DuiLabel *label = new DuiLabel("Hello World!");
	mainLayout->addItem(label);
}
