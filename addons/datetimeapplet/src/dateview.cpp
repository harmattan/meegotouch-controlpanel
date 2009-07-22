#include "dateview.h"
#include "dcpdatetime.h"
#include "datetimetranslation.h"
#include "dcpspaceritem.h"

#include <DuiWidget>
#include <duicontainer.h>
#include <duilabel.h>
#include <duiscenemanager.h>
#include <duicalendar.h>
#include <QDateTime>
#include <QGraphicsLinearLayout>

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
    QGraphicsLinearLayout *widgetLayout = new QGraphicsLinearLayout(Qt::Vertical, centralWidget);
    widgetLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    widgetLayout->setSpacing(1);

    // labelLayout
    QGraphicsLinearLayout *labelLayout = new QGraphicsLinearLayout(Qt::Horizontal, 0);
    labelLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    labelLayout->setSpacing(1);

    // labelVLayout
    QGraphicsLinearLayout *labelVLayout = new QGraphicsLinearLayout(Qt::Vertical, 0);
    labelVLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    labelVLayout->setSpacing(1);

    // m_DateLabel
    m_DateLabel = new DuiLabel(QDateTime::currentDateTime().toString("MMM dd"), this);
    m_DateLabel->setObjectName("DateViewLabel");
    m_DateLabel->setAlignment(Qt::AlignCenter);

    DuiCalendar calendar;
    calendar.setDateTime(QDateTime::currentDateTime());
    
    // m_WeekLabel
    m_WeekLabel = new DuiLabel("Week " + QString::number(calendar.weekOfYear()), this);
    m_WeekLabel->setObjectName("WeekViewLabel");
    m_WeekLabel->setAlignment(Qt::AlignCenter);

    // add items to labelVLayoutPolicy
    labelVLayout->addItem(m_DateLabel);
    labelVLayout->setAlignment(m_DateLabel, Qt::AlignCenter);
    labelVLayout->addItem(m_WeekLabel);
    labelVLayout->setAlignment(m_WeekLabel, Qt::AlignCenter);

    // add items to labelLayoutPolicy
    labelLayout->addItem(new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Fixed));
    labelLayout->addItem(labelVLayout);
    labelLayout->addItem(new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding ,QSizePolicy::Fixed));
    
    // add items to widgetLayoutPolicy
    widgetLayout->addItem(labelLayout);
    
    // setCentralWidget
    m_Container->setCentralWidget(centralWidget);

    // add items to mainLayoutPolicy
    mainLayout->addItem(m_Container);
    mainLayout->setAlignment(m_Container, Qt::AlignCenter);
}

