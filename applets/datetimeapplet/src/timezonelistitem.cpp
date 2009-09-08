#include "timezonelistitem.h"
#include "dcptimezonedata.h"

#include <QGraphicsGridLayout>
#include <QSizePolicy>
#include <duibutton.h>
#include <duilabel.h>
#include <duiseparator.h>
#include <QGraphicsSceneMouseEvent>

const int height = 75;
static const QString separatorObjectName = "DcpSmallSeparator";

TimeZoneListItem::TimeZoneListItem(QString timezone, QString country, QString gmt, 
                                   QString city, DuiWidget *parent)
                 :DuiWidget(parent),
                  m_TimeZone(timezone),
                  m_Country(country),
                  m_Gmt(gmt),
                  m_City(city),
                  m_Checked(false),
                  m_Filtered(true)
{
    initWidget();
}

TimeZoneListItem::~TimeZoneListItem()
{
}

QString TimeZoneListItem::timeZone()
{
    return m_TimeZone;
}

QString TimeZoneListItem::country()
{
    return m_Country;
}

QString TimeZoneListItem::gmt()
{
    return m_Gmt;
}

QString TimeZoneListItem::city()
{
    return m_City;
}

void TimeZoneListItem::checked(bool ok)
{
    m_Checked = ok;
    m_CheckMark->setVisible(m_Checked);
    if (m_Checked) {
        m_CountryLabel->setObjectName("CountryLabelSelected");
        m_GmtCityLabel->setObjectName("GmtCityLabelSelected");
    } else {
        m_CountryLabel->setObjectName("CountryLabel");
        m_GmtCityLabel->setObjectName("GmtCityLabel");
    }
}

bool TimeZoneListItem::isChecked()
{
    return m_Checked;
}

void TimeZoneListItem::filtered(bool ok)
{
    m_Filtered = ok;
}

bool TimeZoneListItem::isFiltered()
{
    return m_Filtered;
}

void TimeZoneListItem::setVisibleSeparator(bool enable)
{
    m_GraySeparator->setVisible(enable);
}

void TimeZoneListItem::activate()
{
    m_CountryLabel->setVisible(true);
    m_GmtCityLabel->setVisible(true);
}

void TimeZoneListItem::initWidget()
{
    // mainLayout
    QGraphicsGridLayout *mainLayout = new QGraphicsGridLayout(this);
    mainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    mainLayout->setSpacing(0);

    // set height
    this->setMinimumHeight(height);
    this->setMaximumHeight(height);

    // m_CountryLabel
    m_CountryLabel = new DuiLabel(m_Country, this);
    m_CountryLabel->setObjectName("CountryLabel");
    m_CountryLabel->setAlignment(Qt::AlignBottom);
    m_CountryLabel->setVisible(false);

    // m_GmtCityLabel
    m_GmtCityLabel = new DuiLabel(m_Gmt + " " + m_City, this);
    m_GmtCityLabel->setObjectName("GmtCityLabel");
    m_GmtCityLabel->setAlignment(Qt::AlignTop);
    m_GmtCityLabel->setVisible(false);

    mainLayout->addItem(m_CountryLabel, 0,0);
    mainLayout->addItem(m_GmtCityLabel, 1,0);

    // m_CheckMark
    m_CheckMark = new DuiButton(this);
    m_CheckMark->setObjectName("TimeZoneCheckMark");
    m_CheckMark->setAcceptedMouseButtons(0);
    m_CheckMark->setVisible(false);

    // m_GreySeparator
    m_GraySeparator = new DuiSeparator(this);
    m_GraySeparator->setObjectName(separatorObjectName);

    mainLayout->addItem(m_CheckMark, 0,1, 2,1, Qt::AlignCenter);
    mainLayout->addItem(m_GraySeparator, 2,0, 1,2, Qt::AlignRight);
}

void TimeZoneListItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    DuiWidget::mousePressEvent(event);
    event->accept();
    emit clicked(this);
}

void TimeZoneListItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    DuiWidget::mouseReleaseEvent(event);
    event->accept();
}


