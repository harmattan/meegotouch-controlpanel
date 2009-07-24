#include "dateview.h"
#include "dcpdatetime.h"
#include "datetimetranslation.h"
#include "dcpspaceritem.h"
#include "stepbutton.h"
#include "datepicker.h"

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
    QGraphicsLinearLayout *widgetLayout = new QGraphicsLinearLayout(Qt::Horizontal, centralWidget);
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

    // pickerLayout
    QGraphicsLinearLayout *pickerLayout = new QGraphicsLinearLayout(Qt::Vertical, 0);
    pickerLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    pickerLayout->setSpacing(1);

    // leftStepButton
    StepButton *leftStepButton = new StepButton(StepButton::Left, this);
    leftStepButton->setMinimumSize(QSize(20, 40));
    leftStepButton->setMaximumSize(QSize(20, 40));

    // rightStepButton
    StepButton *rightStepButton = new StepButton(StepButton::Right, this);
    rightStepButton->setMinimumSize(QSize(20, 40));
    rightStepButton->setMaximumSize(QSize(20, 40));

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

    // datePicker
    DatePicker *datePicker = new DatePicker(this);
    connect(leftStepButton, SIGNAL(clicked()), datePicker, SLOT(left()));
    connect(rightStepButton, SIGNAL(clicked()), datePicker, SLOT(right()));
    
    // add items to labelVLayoutPolicy
    labelVLayout->addItem(m_DateLabel);
    labelVLayout->setAlignment(m_DateLabel, Qt::AlignCenter);
    labelVLayout->addItem(m_WeekLabel);
    labelVLayout->setAlignment(m_WeekLabel, Qt::AlignCenter);

    // add items to labelLayoutPolicy
    labelLayout->addItem(leftStepButton);
    labelLayout->setAlignment(leftStepButton, Qt::AlignCenter);
    labelLayout->addItem(new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Fixed));
    labelLayout->addItem(labelVLayout);
    labelLayout->addItem(new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding ,QSizePolicy::Fixed));
    labelLayout->addItem(rightStepButton);
    labelLayout->setAlignment(rightStepButton, Qt::AlignCenter);
    
    // add items to pickerLayout
    pickerLayout->addItem(labelLayout);
    pickerLayout->addItem(datePicker);
    
    // add items to widgetLayoutPolicy
    widgetLayout->addItem(new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Preferred));
    widgetLayout->addItem(pickerLayout);
    widgetLayout->addItem(new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Preferred));
    
    // setCentralWidget
    m_Container->setCentralWidget(centralWidget);

    // add items to mainLayoutPolicy
    mainLayout->addItem(m_Container);
    mainLayout->setAlignment(m_Container, Qt::AlignCenter);
}

