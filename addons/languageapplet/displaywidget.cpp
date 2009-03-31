#include "displaywidget.h"

#include <duitheme.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duilist.h>
#include "dcplanguage.h"

const QString cssDir = "/usr/share/themes/dui/duicontrolpanel/";

DisplayWidget::DisplayWidget(QGraphicsWidget *parent)
              :DcpWidget(parent)
{
    // DuiTheme::loadCSS(cssDir + "languageapplet.css");
    setReferer(DcpLanguage::Main);
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
    DuiList *inDeviceList = new DuiList(this);
    
    // Layout
    DuiLayout *mainLayout = new DuiLayout(this);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    
    mainLayoutPolicy->setContentsMargins(12.0, 12.0, 12.0, 12.0);
    mainLayoutPolicy->setSpacing(15);

    mainLayoutPolicy->addItemAtPosition(inDeviceList, 0, Qt::AlignCenter);
}
