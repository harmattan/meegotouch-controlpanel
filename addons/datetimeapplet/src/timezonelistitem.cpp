#include "timezonelistitem.h"
#include "dcpspaceritem.h"
#include "dcptimezonedata.h"

#include <duilayout.h>
#include <duigridlayoutpolicy.h>
#include <duilinearlayoutpolicy.h>
#include <duibutton.h>
#include <duilabel.h>
#include <duiseparator.h>
#include <duiscenemanager.h>
#include <QGraphicsSceneMouseEvent>

const int height = 75;

TimeZoneListItem::TimeZoneListItem(QString country, QString gmt, QString city, DuiWidget *parent)
                 :DuiWidget(parent),
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

    if (m_Checked) {
        m_CountryLabel->setText("<font color=#e48415>" + m_Country +
                                "</font>");
        m_GmtCityLabel->setText("<font color=#e48415>" + m_Gmt + " "
                                + m_City + "</font>");
        m_CheckMark->setVisible(true);
    } else {
        m_CountryLabel->setText("<font color=#ffffff>" + m_Country +
                                "</font>");
        m_GmtCityLabel->setText("<font color=#ffffff>" + m_Gmt + " "
                                + m_City + "</font>");
        m_CheckMark->setVisible(false);
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

void TimeZoneListItem::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
    mainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
        new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setSpacing(5);
    
    // set height
    this->setMinimumHeight(height);
    this->setMaximumHeight(height);

    // LabelLayout
    m_LabelLayout = new DuiLayout(0);
    m_LabelLayout->setAnimator(0);
    m_LabelLayout->setContentsMargins(20.0, 0.0, 20.0, 0.0);
    m_LabelLayoutPolicy = new DuiGridLayoutPolicy(m_LabelLayout);
    m_LabelLayout->setPolicy(m_LabelLayoutPolicy);
    m_LabelLayoutPolicy->setSpacing(3);

    // textLayout
    DuiLayout *textLayout = new DuiLayout(0);
    textLayout->setAnimator(0);
    textLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    DuiLinearLayoutPolicy *textLayoutPolicy =
        new DuiLinearLayoutPolicy(textLayout, Qt::Vertical);
    textLayout->setPolicy(textLayoutPolicy);
    textLayoutPolicy->setSpacing(1);

    // m_CountryLabel
    m_CountryLabel = new DuiLabel("<font color=#ffffff>" + m_Country +
                                  "</font>", this);
    m_CountryLabel->setObjectName("CountryLabel");

    // m_GmtCityLabel
    m_GmtCityLabel = new DuiLabel("<font color=#ffffff>" + m_Gmt + " " 
                                  + m_City + "</font>", this);
    m_GmtCityLabel->setObjectName("GmtCityLabel");

    // Add items to textLayoutPolicy
    textLayoutPolicy->addItemAtPosition(m_CountryLabel, 0, Qt::AlignLeft | Qt::AlignVCenter);
    textLayoutPolicy->addItemAtPosition(m_GmtCityLabel, 1, Qt::AlignLeft | Qt::AlignVCenter);
    
    // checkMarkLayout
    DuiLayout *checkMarkLayout = new DuiLayout(0);
    checkMarkLayout->setAnimator(0);
    checkMarkLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    DuiLinearLayoutPolicy *checkMarkLayoutPolicy =
        new DuiLinearLayoutPolicy(checkMarkLayout, Qt::Vertical);
    checkMarkLayout->setPolicy(checkMarkLayoutPolicy);
    checkMarkLayoutPolicy->setSpacing(1);
    
    // m_CheckMark
    m_CheckMark = new DuiButton(this);
    m_CheckMark->setObjectName("TimeZoneCheckMark");
    m_CheckMark->setAcceptedMouseButtons(0);
    m_CheckMark->setMinimumSize(QSize(32, 32));
    m_CheckMark->setMaximumSize(QSize(32, 32));
    m_CheckMark->setVisible(false);

    // Add items to checkMarkLayoutPolicy
    checkMarkLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding),
            0, Qt::AlignCenter);
    checkMarkLayoutPolicy->addItemAtPosition(m_CheckMark, 1, Qt::AlignCenter);
    checkMarkLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding ,QSizePolicy::Expanding),
            2, Qt::AlignCenter);

    // Add items to m_LabelLayoutPolicy
    m_LabelLayoutPolicy->addItemAtPosition(textLayout, 0, 0);
    m_LabelLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding),
            0, 1);
    m_LabelLayoutPolicy->addItemAtPosition(checkMarkLayout, 0, 2);

    // m_GreySeparator
    m_GraySeparator = new DuiSeparator(this);

    // Add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(m_LabelLayout, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_GraySeparator, 1, Qt::AlignCenter);

    
    connect(DuiSceneManager::instance(), SIGNAL(orientationChanged(const Dui::Orientation &)),
            this, SLOT(onOrientationChanged()));
    onOrientationChanged();
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

void TimeZoneListItem::onOrientationChanged()
{
    /* DuiSceneManager* manager = DuiSceneManager::instance();
    if (manager == 0) return;

    switch (manager->orientation()) {
        case Dui::Landscape:
            this->setMinimumWidth(manager->visibleSceneRect().width() / 2 - 40);
            this->setMaximumWidth(manager->visibleSceneRect().width() / 2 - 40);
            break;
        case Dui::Portrait:
            this->setMinimumWidth(manager->visibleSceneRect().width() - 40);
            this->setMaximumWidth(manager->visibleSceneRect().width() - 40);
            break;
        default:
            break;
    }*/
}

