#include "timezonecontainer.h"
#include "timezonelistitem.h"
#include "dcptimezoneconf.h"
#include "dcptimezonedata.h"
#include "dcpspaceritem.h"

#include <duilayout.h>
#include <duigridlayoutpolicy.h>
#include <qtimer.h>
#include <duiscenemanager.h>

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
    delete m_MainLayoutPolicy;
    m_MainLayoutPolicy = new DuiGridLayoutPolicy(m_MainLayout);
    m_MainLayout->setPolicy(m_MainLayoutPolicy);
    m_MainLayoutPolicy->setSpacing(10);

    // add Items to m_MainLayoutPolicy
    int count = 0;
    QMapIterator<int, TimeZoneListItem*> iter(m_ItemMap);
    while (iter.hasNext()) {
        iter.next();
        if (iter.value()->isFiltered()) {
            m_MainLayoutPolicy->addItemAtPosition(iter.value(), count / 2, count % 2);
            iter.value()->setVisible(true);
            count++;
        }
    }

    if (m_MainLayout->count() == 1) {
        m_MainLayoutPolicy->addItemAtPosition(
                new DcpSpacerItem(this, 
                    DuiSceneManager::instance()->visibleSceneRect().width() / 2 - 35, 
                    10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                0, 1);
    } else if (m_MainLayout->count() == 0) {
        m_MainLayoutPolicy->addItemAtPosition(
                new DcpSpacerItem(this, 
                    DuiSceneManager::instance()->visibleSceneRect().width() / 2 - 35, 
                    10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                0, 0);
        m_MainLayoutPolicy->addItemAtPosition(
                new DcpSpacerItem(this, 
                    DuiSceneManager::instance()->visibleSceneRect().width() / 2 - 35, 
                    10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                0, 1);
    }
}

void TimeZoneContainer::initWidget()
{
    // m_MainLayout
    m_MainLayout = new DuiLayout(this);
    m_MainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    this->setLayout(m_MainLayout);
    m_MainLayoutPolicy = new DuiGridLayoutPolicy(m_MainLayout);
    m_MainLayoutPolicy->setSpacing(10);
    m_MainLayout->setPolicy(m_MainLayoutPolicy);

    // add items to m_ItemMap
    QMap<int, DcpTimeZoneData*> zoneMap = DcpTimeZoneConf::instance()->getMap();
    QMapIterator<int, DcpTimeZoneData*> zoneIter(zoneMap);
    int count = 0;
    while (zoneIter.hasNext()) {
        zoneIter.next();
        if (zoneIter.value()->country() == "Europe") {
            m_ItemMap[count++] = new TimeZoneListItem(zoneIter.value()->country(),
                                                      zoneIter.value()->gmt(),
                                                      zoneIter.value()->city(), 
                                                      this);
        }
    }
    zoneMap.clear();
    
    // add items to mainLayoutPolicy
    QMapIterator<int, TimeZoneListItem*> iter(m_ItemMap);
    while (iter.hasNext()) {
        iter.next();
        m_MainLayoutPolicy->addItemAtPosition(iter.value(), iter.key() / 2, iter.key() % 2);
        connect(iter.value(), SIGNAL(clicked(TimeZoneListItem*)), 
                this, SLOT(itemClicked(TimeZoneListItem*)));
    }
    
    if (m_ItemMap.size() % 2 == 0) {
        m_ItemMap[m_ItemMap.size() - 1]->setVisibleSeparator(false);
        m_ItemMap[m_ItemMap.size() - 2]->setVisibleSeparator(false);
    } else {
        m_ItemMap[m_ItemMap.size() - 1]->setVisibleSeparator(false);
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
    emit closing();
}
