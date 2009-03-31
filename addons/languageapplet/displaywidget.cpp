#include "displaywidget.h"

#include <duitheme.h>

const QString cssDir = "/usr/share/themes/dui/duicontrolpanel";

DisplayWidget::DisplayWidget(QGraphicsWidget *parent)
              :DcpWidget(parent)
{
    DuiTheme::loadCSS(cssDir + "languageapplet.css");
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
}
