#include "timezonecontainer.h"
#include "timezonelistitem.h"
#include "dcptimezoneconf.h"
#include "dcptimezonedata.h"
#include "dcpspaceritem.h"

#include <duilayout.h>
#include <duigridlayoutpolicy.h>
#include <qtimer.h>
#include <duiscenemanager.h>
#include <duiicuconversions.h>
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
    /*
    for (int i = m_MainLayout->count() - 1; i >= 0; i--) {
        static_cast<TimeZoneListItem*>(m_MainLayout->itemAt(i))->setVisible(false);
        m_MainLayout->removeAt(i);
    }
    delete m_MainLayoutPolicy;
    m_MainLayoutPolicy = new DuiGridLayoutPolicy(m_MainLayout);
    m_MainLayout->setPolicy(m_MainLayoutPolicy);
    m_MainLayoutPolicy->setSpacing(10);

    // add Items to m_MainLayoutPolicy
    int count = 0;
    QMapIterator<int, TimeZoneListItem*> iter(m_ItemMap);
    while (iter.hasNext()) {
        iter.next();
        iter.value()->setVisibleSeparator(true);
        if (iter.value()->isFiltered()) {
            m_MainLayoutPolicy->addItemAtPosition(iter.value(), count / 2, count % 2);
            iter.value()->setVisible(true);
            count++;
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
            static_cast<TimeZoneListItem*>(m_MainLayout->itemAt(count - 1))->setVisibleSeparator(false);
            static_cast<TimeZoneListItem*>(m_MainLayout->itemAt(count - 2))->setVisibleSeparator(false);
        } else {
            static_cast<TimeZoneListItem*>(m_MainLayout->itemAt(count - 1))->setVisibleSeparator(false);
        }
    }

    if (m_MainLayout->count() == 1) {
        m_MainLayoutPolicy->addItemAtPosition(
                new DcpSpacerItem(this, 
                    DuiSceneManager::instance()->visibleSceneRect().width() / 2 - 40, 
                    10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                0, 1);
    } */
}

void TimeZoneContainer::initWidget()
{
    // m_MainLayout
    m_MainLayout = new DuiLayout(this);
    m_MainLayout->setAnimator(0);
    m_MainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    this->setLayout(m_MainLayout);
    m_MainLayoutPolicy = new DuiGridLayoutPolicy(m_MainLayout);
    m_MainLayoutPolicy->setSpacing(10);
    m_MainLayout->setPolicy(m_MainLayoutPolicy);

    // add items to m_ItemMap
    qDebug() << "ADD ITEMS TO ZONE ITEMMAP";
    QMap<int, DcpTimeZoneData*> zoneMap = DcpTimeZoneConf::instance()->getMap();
    QMapIterator<int, DcpTimeZoneData*> zoneIter(zoneMap);
    int count = 0;
    while (zoneIter.hasNext()) {
        zoneIter.next();
        m_ItemMap[count++] = new TimeZoneListItem(zoneIter.value()->country(),
                                                  zoneIter.value()->gmt(),
                                                  zoneIter.value()->city(), 
                                                  this);
    }
    zoneMap.clear();
    
    // add items to mainLayoutPolicy
    qDebug() << "ADD ITEMS TO LAYOUT";
    QMapIterator<int, TimeZoneListItem*> iter(m_ItemMap);
    while (iter.hasNext()) {
        iter.next();
        m_MainLayoutPolicy->addItemAtPosition(iter.value(), iter.key() / 2, iter.key() % 2);
        connect(iter.value(), SIGNAL(clicked(TimeZoneListItem*)), 
                this, SLOT(itemClicked(TimeZoneListItem*)));
        if (iter.value()->city() == "London")
            iter.value()->checked(true);
    }
    
    if (m_ItemMap.size() % 2 == 0) {
        m_ItemMap[m_ItemMap.size() - 1]->setVisibleSeparator(false);
        m_ItemMap[m_ItemMap.size() - 2]->setVisibleSeparator(false);
    } else {
        m_ItemMap[m_ItemMap.size() - 1]->setVisibleSeparator(false);
    }

    qDebug() << "FINISHED Add";
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
    UnicodeString zoneName =
        DuiIcuConversions::qStringToUnicodeString(item->country() + "/" + item->city());
    qDebug() << "TimeZone Name: " << DuiIcuConversions::unicodeStringToQString(zoneName);
    icu::TimeZone *zone = icu::TimeZone::createTimeZone(zoneName);
    icu::TimeZone::setDefault(*zone);
    
    emit closing();
}
