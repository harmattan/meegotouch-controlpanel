#include "timezonecontainer.h"
#include "timezonelistitem.h"
#include "dcptimezoneconf.h"
#include "dcptimezonedata.h"
#include "dcpspaceritem.h"
#include "dcpicuconversions.h"

#include <unicode/timezone.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duigridlayoutpolicy.h>
#include <qtimer.h>
#include <duiscenemanager.h>
#include <QDebug>

TimeZoneContainer::TimeZoneContainer(DuiWidget *parent)
                  :DuiWidget(parent)
{
    initWidget();
}

TimeZoneContainer::~TimeZoneContainer()
{
    m_ItemMap.clear();
}

QMap<int, TimeZoneListItem*> TimeZoneContainer::getMap()
{
    return m_ItemMap;
}

void TimeZoneContainer::updateLayout()
{
    for (int i = m_MainLayout->count() - 1; i >= 0; i--) {
        static_cast<TimeZoneListItem*>(m_MainLayout->itemAt(i))->setVisible(false);
        m_MainLayout->removeAt(i);
    }
    // delete policies
    delete m_MainLayoutPolicy;
    delete m_MainVLayoutPolicy;
    
    m_MainLayoutPolicy = new DuiGridLayoutPolicy(m_MainLayout);
    m_MainLayoutPolicy->setSpacing(10);
    m_MainVLayoutPolicy = new DuiLinearLayoutPolicy(m_MainLayout, Qt::Vertical);
    m_MainVLayoutPolicy->setSpacing(5);

    // add Items to m_MainLayoutPolicy
    int count = 0;
    QMapIterator<int, TimeZoneListItem*> iter(m_ItemMap);
    while (iter.hasNext()) {
        iter.next();
        iter.value()->setVisibleSeparator(true);
        if (iter.value()->isFiltered()) {
            m_MainLayoutPolicy->addItemAtPosition(iter.value(), count / 2, count % 2);
            m_MainVLayoutPolicy->addItemAtPosition(iter.value(), count++, 
                                                   Qt::AlignLeft | Qt::AlignVCenter);
            iter.value()->setVisible(true);
        }
    }

    if (m_MainLayout->count() == 0) {
        m_MainLayoutPolicy->addItemAtPosition(
                new DcpSpacerItem(this, 
                    DuiSceneManager::instance()->visibleSceneRect().width() / 2 - 40, 
                    10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                0, 0);
        m_MainLayoutPolicy->addItemAtPosition(
                new DcpSpacerItem(this, 
                    DuiSceneManager::instance()->visibleSceneRect().width() / 2 - 40, 
                    10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                0, 1);
    } else {
        int count = m_MainLayout->count();
        if (count % 2 == 0) {
            static_cast<TimeZoneListItem*>(
                            m_MainLayout->itemAt(count - 1))->setVisibleSeparator(false);
            static_cast<TimeZoneListItem*>(
                            m_MainLayout->itemAt(count - 2))->setVisibleSeparator(false);
        } else {
            static_cast<TimeZoneListItem*>(
                            m_MainLayout->itemAt(count - 1))->setVisibleSeparator(false);
        }
    }

    if (m_MainLayout->count() == 1) {
        m_MainLayoutPolicy->addItemAtPosition(
                new DcpSpacerItem(this, 
                    DuiSceneManager::instance()->visibleSceneRect().width() / 2 - 40, 
                    10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                0, 1);
    }

    orientationChanged();
}

void TimeZoneContainer::initWidget()
{
    // m_MainLayout
    m_MainLayout = new DuiLayout(this);
    m_MainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    this->setLayout(m_MainLayout);

    // m_MainLayoutPolicy
    m_MainLayoutPolicy = new DuiGridLayoutPolicy(m_MainLayout);
    m_MainLayoutPolicy->setSpacing(10);

    // m_MainVLayoutPolicy
    m_MainVLayoutPolicy = new DuiLinearLayoutPolicy(m_MainLayout, Qt::Vertical);
    m_MainVLayoutPolicy->setSpacing(5);
    
    m_MainLayout->setPolicy(m_MainLayoutPolicy);

    // add items to m_ItemMap
    QMultiMap<QString, DcpTimeZoneData*> zoneMap = DcpTimeZoneConf::instance()->getMap();
    QMapIterator<QString, DcpTimeZoneData*> zoneIter(zoneMap);
    int count = 0;
    while (zoneIter.hasNext()) {
        zoneIter.next();
        m_ItemMap[count++] = new TimeZoneListItem(zoneIter.value()->timeZone(),
                                                  zoneIter.value()->country(),
                                                  zoneIter.value()->gmt(),
                                                  zoneIter.value()->city(), 
                                                  this);
    }
    zoneMap.clear();
    
    // add items to mainLayoutPolicy
    QMapIterator<int, TimeZoneListItem*> iter(m_ItemMap);
    count = 0;
    while (iter.hasNext()) {
        iter.next();
        m_MainLayoutPolicy->addItemAtPosition(iter.value(), iter.key() / 2, iter.key() % 2);
        m_MainVLayoutPolicy->addItemAtPosition(iter.value(), count++, Qt::AlignLeft | Qt::AlignVCenter);
        connect(iter.value(), SIGNAL(clicked(TimeZoneListItem*)), 
                this, SLOT(itemClicked(TimeZoneListItem*)));
        QString current = DcpTimeZoneConf::instance()->defaultTimeZone().city();
        if (iter.value()->city() == current)
            iter.value()->checked(true);
    }
    
    if (m_ItemMap.size() % 2 == 0) {
        m_ItemMap[m_ItemMap.size() - 1]->setVisibleSeparator(false);
        m_ItemMap[m_ItemMap.size() - 2]->setVisibleSeparator(false);
    } else {
        m_ItemMap[m_ItemMap.size() - 1]->setVisibleSeparator(false);
    }

    // orientation change
    connect(DuiSceneManager::instance(), SIGNAL(orientationChanged(const Dui::Orientation &)),
            this, SLOT(orientationChanged()));
    orientationChanged();
}

void TimeZoneContainer::orientationChanged()
{
    DuiSceneManager *manager = DuiSceneManager::instance();
    if (manager == 0)
        return;

    switch (manager->orientation()) {
        case Dui::Landscape:
            m_MainLayout->setPolicy(m_MainLayoutPolicy);
            updateGridSeparator();
            break;
        case Dui::Portrait:
            m_MainLayout->setPolicy(m_MainVLayoutPolicy);
            updateHSeparator();
            break;
        default:
            break;
    }
}

void TimeZoneContainer::itemClicked(TimeZoneListItem *item)
{
    QMapIterator<int, TimeZoneListItem*> iter(m_ItemMap);
    while (iter.hasNext()) {
        iter.next();
        iter.value()->checked(false);
    }
    item->checked(true);

    // set default time zone
    DcpTimeZoneConf::instance()->setDefaultTimeZone(item->timeZone());
}

void TimeZoneContainer::updateGridSeparator()
{
    if (m_MainLayout->count() > 2) {
        if (m_MainLayout->count() % 2 == 0) {
            static_cast<TimeZoneListItem*>(
                    m_MainLayout->itemAt(m_MainLayout->count() - 2))->setVisibleSeparator(false);
        }
    }
}

void TimeZoneContainer::updateHSeparator()
{
    if (m_MainLayout->count() > 2) {
        static_cast<TimeZoneListItem*>(
                m_MainLayout->itemAt(m_MainLayout->count() - 2))->setVisibleSeparator(true);
    }
}

