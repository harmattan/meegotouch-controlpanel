#include "timezonecontainer.h"
#include "timezonelistitem.h"
#include "dcptimezoneconf.h"
#include "dcptimezonedata.h"

#include <duilayout.h>
#include <duigridlayoutpolicy.h>
#include <qtimer.h>

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

void TimeZoneContainer::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
    mainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    this->setLayout(mainLayout);
    DuiGridLayoutPolicy *mainLayoutPolicy =
        new DuiGridLayoutPolicy(mainLayout);
    mainLayoutPolicy->setSpacing(10);

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
        mainLayoutPolicy->addItemAtPosition(iter.value(), iter.key() / 2, iter.key() % 2);
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
