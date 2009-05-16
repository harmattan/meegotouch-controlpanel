#include "datetimewidget.h"
#include "dcpbutton.h"
#include "dcpwidgettypes.h"
#include <duitheme.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duiscenemanager.h>
const QString cssDir = "/usr/share/themes/dui/duicontrolpanel/";
const int widgetWidth = 100;

DateTimeWidget::DateTimeWidget(QGraphicsWidget *parent)
	    :DcpWidget(parent)
{
    //DuiTheme::loadCSS(cssDir + "displayapplet.css");
    initWidget();
}

DateTimeWidget::~DateTimeWidget()
{
}

void DateTimeWidget::paint(QPainter *painter,
			const QStyleOptionGraphicsItem *option,
			QWidget *widget)
{
	Q_UNUSED(painter);
	Q_UNUSED(option);
	Q_UNUSED(widget);

/*    QPen pen(QColor(120, 120, 120, 240));
    QBrush brush(QColor(20, 20, 20, 240));
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(QRectF(0.0, 0.0,
                             size().width(),
                             size().height()));
*/
}

void DateTimeWidget::initWidget()
{
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
    this->setLayout(mainLayout);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    mainLayoutPolicy->setSpacing(1);
    
    DuiLayout *dateTimeLayout = new DuiLayout(0);
    dateTimeLayout->setAnimator(0);
    DuiLinearLayoutPolicy *dateTimeLayoutPolicy =
            new DuiLinearLayoutPolicy(dateTimeLayout, Qt::Horizontal);
    dateTimeLayout->setPolicy(dateTimeLayoutPolicy);
    dateTimeLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    dateTimeLayoutPolicy->setSpacing(1);
    m_DateButton = new DcpButton(DCPLABEL2);
    m_DateButton->setText("Date", "Monday, 14 May 2009");   
    m_DateButton->setLine(true);
    m_DateButton->setMaximumHeight(90);  
    m_TimeButton = new DcpButton(DCPLABEL2);
    m_TimeButton->setText("Current Time", "9:44 AM");   
    m_TimeButton->setLine(true);   
    m_TimeZoneButton = new DcpButton(DCPLABEL2);
    m_TimeZoneButton->setText("Current Time Zone", "+ 1 GMT London");   
    m_TimeZoneButton->setLine(true);
    m_TimeZoneButton->setMinimumWidth(DuiSceneManager::instance()->visibleSceneRect().width());
// regionFormatButton                                                       
    DuiButton *m_RegionFormatButton = new DuiButton("Region Format"
     , this);
    m_RegionFormatButton->setObjectName("RegionFormatButton");
    m_RegionFormatButton->setMaximumWidth(380);                               
    m_RegionFormatButton->setMaximumHeight(60);
    m_RegionFormatButton->setMinimumHeight(60);
    dateTimeLayoutPolicy->addItemAtPosition(m_DateButton, 0, Qt::AlignLeft | Qt::AlignVCenter);
    dateTimeLayoutPolicy->addItemAtPosition(m_TimeButton, 1, Qt::AlignRight | Qt::AlignVCenter);
  
    mainLayoutPolicy->addItemAtPosition(dateTimeLayout, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_TimeZoneButton, 1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_RegionFormatButton, 2, Qt::AlignCenter);

    DuiWidget* spacer = new DuiWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayoutPolicy->addItemAtPosition(spacer, 3, Qt::AlignCenter);
}

