#include "dateview.h"
#include "dcpdatetime.h"
#include "datetimetranslation.h"
#include "dcpspaceritem.h"

#include <DuiWidget>
#include <duicontainer.h>
#include <duilabel.h>
#include <duiscenemanager.h>
#include <QGraphicsLinearLayout>


#include "datepicker/monthwidget.h"
#include "datepicker/monthwidgetview.h"
#include "datepicker/monthwidgetfullview.h"

DateView::DateView(QGraphicsWidget *parent)
           :DcpWidget(parent)
{
    setReferer(DcpDateTime::Main);
    initWidget();
}

DateView::~DateView()
{
}

void DateView::initWidget()
{
    // mainLayout
    QGraphicsLinearLayout *mainLayout = new QGraphicsLinearLayout(Qt::Vertical, this);
    mainLayout->setContentsMargins(0.0, 12.0, 0.0, 12.0);
    mainLayout->setSpacing(1);

    m_Container = new DuiContainer(DcpDateTime::DateDialogTitle, this);
    
    // centralWidget
    DuiWidget *centralWidget = new DuiWidget(0);
    
    // widgetLayout
    QGraphicsLinearLayout *widgetLayout = new QGraphicsLinearLayout(Qt::Horizontal, centralWidget);
    widgetLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    widgetLayout->setSpacing(1);

  	//widgetLayout->addItem(pickerLayout);

    // setCentralWidget

	m_MonthWidget = new MonthWidget();

	MonthWidgetFullView* tmpView = new MonthWidgetFullView(m_MonthWidget);

	m_MonthWidget->setView(tmpView);

    m_Container->setCentralWidget(m_MonthWidget);

    // add items to mainLayoutPolicy
    mainLayout->addItem(m_Container);
    mainLayout->setAlignment(m_Container, Qt::AlignCenter);

}


