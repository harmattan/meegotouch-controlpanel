#include "datetimewidget.h"
#include "dcpbutton.h"
#include "dcpwidgettypes.h"
#include "dcpspaceritem.h"
#include "updatebutton.h"
#include "datetimetranslation.h"
#include "timezonedialog.h"

#include <duitheme.h>
#include <duilayout.h>
#include <duilocale.h>
#include <duilabel.h>
#include <duilinearlayoutpolicy.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duiscenemanager.h>
#include <QDateTime>
#include <QTimer>

const QString cssDir = "/usr/share/themes/dui/duicontrolpanel/";
const int widgetWidth = 100;

DateTimeWidget::DateTimeWidget(QGraphicsWidget *parent)
	    :DcpWidget(parent),
         m_Dlg(0)
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

bool DateTimeWidget::back()
{
    if (m_Dlg) {
        m_Dlg->close();
        return false;
    } else {
        return DcpWidget::back();
    }
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
    mainLayoutPolicy->setSpacing(0);
    
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
    this->updateDateText();
    m_DateButton->setLine(true);
    m_DateButton->setMaximumHeight(90);  
    
    // m_TimeButton
    m_TimeButton = new DcpButton(DCPLABEL2);
    this->updateTimeText();
    m_TimeButton->setLine(true);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimeText()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateDateText()));
    timer->start(1000);   
    
    // m_TimeZoneButton
    DuiLocale locale;
    m_TimeZoneButton = new DcpButton(DCPLABEL2);
    m_TimeZoneButton->setText(DcpDateTime::CurrentTimeZoneText, locale.countryEndonym());   
    m_TimeZoneButton->setLine(true);
    m_TimeZoneButton->setMinimumWidth(DuiSceneManager::instance()->visibleSceneRect().width()-30);
    connect(m_TimeZoneButton, SIGNAL(clicked()), this, SLOT(showTimeZoneDialog()));
    
    // m_AutomaticUpdateButton
    m_AutomaticUpdateButton = new UpdateButton(this);
    m_AutomaticUpdateButton->setMinimumWidth(
            DuiSceneManager::instance()->visibleSceneRect().width() - 30);
    
    // simpleLabel
    DuiLabel *simpleLabel = new DuiLabel(DcpDateTime::SetDateTimeText, this);
    simpleLabel->setObjectName("SimpleLabel");
    simpleLabel->setAlignment(Qt::AlignCenter);
    
    // regionFormatButton                                                       
    DuiButton *m_RegionFormatButton = new DuiButton(DcpDateTime::RegionButtonText
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

void DateTimeWidget::showTimeZoneDialog()
{
    m_Dlg = new TimeZoneDialog();
    this->setEnabled(false);
    m_Dlg->exec();
    this->setEnabled(true);
    m_Dlg->deleteLater();
    m_Dlg = 0;
}

void DateTimeWidget::updateTimeText()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("h:mm A");
    m_TimeButton->setText(DcpDateTime::CurrentTimeButtonText, text);
}

void DateTimeWidget::updateDateText()
{
    QDateTime date = QDateTime::currentDateTime();
    QString text = date.toString("dddd, dd MMMM yyyy");
    m_DateButton->setText(DcpDateTime::DateButtonText, text);        
}

