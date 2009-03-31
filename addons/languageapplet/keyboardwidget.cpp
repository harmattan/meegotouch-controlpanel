#include "keyboardwidget.h"

#include <duitheme.h>
#include "dcplanguage.h"

const QString cssDir = "/usr/share/themes/dui/duicontrolpanel/";

KeyboardWidget::KeyboardWidget(QGraphicsWidget *parent)
              :DcpWidget(parent)
{
    // DuiTheme::loadCSS(cssDir + "languageapplet.css");
    setReferer(DcpLanguage::Main);
    initWidget();
}

KeyboardWidget::~KeyboardWidget()
{
}

void KeyboardWidget::paint(QPainter *painter,
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

void KeyboardWidget::initWidget()
{
}
