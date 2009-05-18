#include "datetimewidget.h"
#include "dcpbutton.h"
#include "dcpwidgettypes.h"
#include "dcpspaceritem.h"
#include "updatebutton.h"
#include <duitheme.h>
#include <duilayout.h>
#include <duilabel.h>
#include <duilinearlayoutpolicy.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duiscenemanager.h>
const QString cssDir = "/usr/share/themes/dui/duicontrolpanel/";
const int widgetWidth = 100;

DateTimeWidget::DateTimeWidget(QGraphicsWidget *parent)
	    :DcpWidget(parent)
{
    DuiTheme::loadCSS(cssDir + "datetimeapplet.css");
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
}

void DateTimeWidget::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
    this->setLayout(mainLayout);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    mainLayoutPolicy->setSpacing(5);
    
    // dateTimeLayout
    DuiLayout *dateTimeLayout = new DuiLayout(0);
    dateTimeLayout->setAnimator(0);
    DuiLinearLayoutPolicy *dateTimeLayoutPolicy =
            new DuiLinearLayoutPolicy(dateTimeLayout, Qt::Horizontal);
    dateTimeLayout->setPolicy(dateTimeLayoutPolicy);
    dateTimeLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    dateTimeLayoutPolicy->setSpacing(1);
    
    // m_DateButton
    m_DateButton = new DcpButton(DCPLABEL2);
    m_DateButton->setText("Date", "Monday, 14 May 2009");   
    m_DateButton->setLine(true);
    m_DateButton->setMaximumHeight(90);  
    
    // m_TimeButton
    m_TimeButton = new DcpButton(DCPLABEL2);
    m_TimeButton->setText("Current Time", "9:44 AM");   
    m_TimeButton->setLine(true);   
    
    // m_TimeZoneButton
    m_TimeZoneButton = new DcpButton(DCPLABEL2);
    m_TimeZoneButton->setText("Current Time Zone", "+ 1 GMT London");   
    m_TimeZoneButton->setLine(true);
    m_TimeZoneButton->setMinimumWidth(DuiSceneManager::instance()->visibleSceneRect().width());
    
    // m_AutomaticUpdateButton
    m_AutomaticUpdateButton = new UpdateButton(this);   
    
    // simpleLabel
    DuiLabel *simpleLabel = new DuiLabel("To set date and time display formats, go to", this);
    simpleLabel->setObjectName("SimpleLabel");
    simpleLabel->setAlignment(Qt::AlignCenter);
    
    // regionFormatButton                                                       
    DuiButton *m_RegionFormatButton = new DuiButton("Region Format"
     , this);
    m_RegionFormatButton->setObjectName("RegionFormatButton");
    m_RegionFormatButton->setMaximumWidth(310);                               
    m_RegionFormatButton->setMaximumHeight(60);
    m_RegionFormatButton->setMinimumHeight(60);
    
    // Add items to dateTimeLayoutPolicy
    dateTimeLayoutPolicy->addItemAtPosition(m_DateButton, 0, Qt::AlignLeft | Qt::AlignVCenter);
    dateTimeLayoutPolicy->addItemAtPosition(m_TimeButton, 1, Qt::AlignRight | Qt::AlignVCenter);
  
    // Add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(dateTimeLayout, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_TimeZoneButton, 1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_AutomaticUpdateButton, 2, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 20, QSizePolicy::Expanding, QSizePolicy::Fixed),
            3, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(simpleLabel, 4, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_RegionFormatButton, 5, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding),
            6, Qt::AlignCenter);
}

