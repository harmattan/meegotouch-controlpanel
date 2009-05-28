#include "timezonecontainer.h"
#include "timezonelistitem.h"

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
}

QMap<int, TimeZoneListItem*> TimeZoneContainer::getMap()
{
    return m_ItemMap;
}

void TimeZoneContainer::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    // mainLayout->setAnimator(0);
    mainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    this->setLayout(mainLayout);
    DuiGridLayoutPolicy *mainLayoutPolicy =
        new DuiGridLayoutPolicy(mainLayout);
    mainLayoutPolicy->setSpacing(10);

    // temporally: add items to m_ItemMap
    m_ItemMap[0] = new TimeZoneListItem("Afghanistan", "GMT+4:30", "Kabul", this);
    m_ItemMap[1] = new TimeZoneListItem("Australia", "GMT+10:00", "Camberra", this);
    m_ItemMap[2] = new TimeZoneListItem("Australia", "GMT+10:00", "Melbourne", this);
    m_ItemMap[3] = new TimeZoneListItem("Belarus", "GMT+3:00", "Minks", this);
    m_ItemMap[4] = new TimeZoneListItem("Bolivia", "GMT-4:00", "La Paz", this);
    m_ItemMap[5] = new TimeZoneListItem("Brazil", "GMT-3:00", "Brasilia", this);
    m_ItemMap[6] = new TimeZoneListItem("Brazil", "GMT-3:00", "Rio de Janerio", this);
    m_ItemMap[7] = new TimeZoneListItem("Brazil", "GMT-3:00", "Sau Paulo", this);
    m_ItemMap[8] = new TimeZoneListItem("Bulgaria", "GMT+3:00", "Sofia", this);
    m_ItemMap[9] = new TimeZoneListItem("Canada", "GMT-3:00", "Halifax", this);
    m_ItemMap[10] = new TimeZoneListItem("Canada", "GMT-4:00", "Montreal", this);
    m_ItemMap[11] = new TimeZoneListItem("Canada", "GMT-4:00", "Ottawa", this);
    m_ItemMap[12] = new TimeZoneListItem("Canada", "GMT-4:00", "Toronto", this);
    m_ItemMap[13] = new TimeZoneListItem("Finland", "GMT+2:00", "Helsinki", this);
    m_ItemMap[14] = new TimeZoneListItem("Hungary", "GMT+1:00", "Budapest", this);
    m_ItemMap[15] = new TimeZoneListItem("England", "GMT+1:00", "London", this);

    // add items to mainLayoutPolicy
    QMapIterator<int, TimeZoneListItem*> iter(m_ItemMap);
    while (iter.hasNext()) {
        iter.next();
        mainLayoutPolicy->addItemAtPosition(iter.value(), iter.key() / 2, iter.key() % 2);
        connect(iter.value(), SIGNAL(clicked(TimeZoneListItem*)), 
                this, SLOT(itemClicked(TimeZoneListItem*)));
        if (iter.key() == 14 || iter.key() == 15) {
            iter.value()->setVisibleSeparator(false);
        }
        if (iter.key() == 15) {
            iter.value()->checked(true);
        }
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
