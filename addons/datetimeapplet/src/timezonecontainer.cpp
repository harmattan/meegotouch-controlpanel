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
                  :DuiWidget(parent), m_CheckedItem(0)
{
    initWidget();
}

TimeZoneContainer::~TimeZoneContainer()
{
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
    int columnwidth = DuiSceneManager::instance()->visibleSceneSize(
                                              Dui::Landscape).width() / 2 - 20;
    m_MainLayoutPolicy->setColumnFixedWidth(0,columnwidth);
    m_MainVLayoutPolicy = new DuiLinearLayoutPolicy(m_MainLayout, Qt::Vertical);
    m_MainVLayoutPolicy->setSpacing(5);

    // add Items to m_MainLayoutPolicy
    int count = 0;
    QListIterator<TimeZoneListItem*> iter(m_ItemList);
    while (iter.hasNext()) {
        TimeZoneListItem *item = iter.next();
        item->setVisibleSeparator(true);
        if (item->isFiltered()) {
            m_MainLayoutPolicy->addItemAtPosition(item, count / 2, count % 2);
            m_MainVLayoutPolicy->addItemAtPosition(item, count++, 
                                                   Qt::AlignLeft | Qt::AlignVCenter);
            item->setVisible(true);
        }
    }

    if (m_MainLayout->count() == 0) {
        m_MainLayoutPolicy->addItemAtPosition(
                new DcpSpacerItem(this, 
                    DuiSceneManager::instance()->visibleSceneSize().width() / 2 - 40, 
                    10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                0, 0);
        m_MainLayoutPolicy->addItemAtPosition(
                new DcpSpacerItem(this, 
                    DuiSceneManager::instance()->visibleSceneSize().width() / 2 - 40, 
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
                    DuiSceneManager::instance()->visibleSceneSize().width() / 2 - 40, 
                    10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                0, 1);
    }

    orientationChanged();
}

void TimeZoneContainer::addMoreItems()
{
    // add items to m_ItemMap
    QMultiMap<QString, DcpTimeZoneData*> zoneMap = DcpTimeZoneConf::instance()->getMap();
    QMapIterator<QString, DcpTimeZoneData*> zoneIter(zoneMap);
    int count = -1;
    while (zoneIter.hasNext()) {
        zoneIter.next();
        count++;
        if (count < 40) {
            continue;
        }
        
        TimeZoneListItem *item = new TimeZoneListItem(zoneIter.value()->timeZone(),
                                                  zoneIter.value()->country(),
                                                  zoneIter.value()->gmt(),
                                                  zoneIter.value()->city(), 
                                                  this);
        m_ItemList << item;

        // add item to the layout:
        m_MainLayoutPolicy->addItemAtPosition(item, count / 2, count % 2);
        m_MainVLayoutPolicy->addItemAtPosition(item, count, Qt::AlignLeft | Qt::AlignVCenter);
        connect(item, SIGNAL(clicked(TimeZoneListItem*)),
                this, SLOT(itemClicked(TimeZoneListItem*)));

        if (!m_CheckedItem) {
            QString current = DcpTimeZoneConf::instance()->defaultTimeZone().city();
            if (item->city() == current) {
                item->checked(true);
                m_CheckedItem = item;
            }
        }
    }
    orientationChanged();
}

void TimeZoneContainer::initWidget()
{
    // m_MainLayout
    m_MainLayout = new DuiLayout(this);
    m_MainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    m_MainLayout->setAnimator(0);
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
        TimeZoneListItem *item = new TimeZoneListItem(zoneIter.value()->timeZone(),
                                                  zoneIter.value()->country(),
                                                  zoneIter.value()->gmt(),
                                                  zoneIter.value()->city(), 
                                                  this);
        m_ItemList << item;

        // add item to the layout:
        m_MainLayoutPolicy->addItemAtPosition(item, count / 2, count % 2);
        m_MainVLayoutPolicy->addItemAtPosition(item, count, Qt::AlignLeft | Qt::AlignVCenter);
        connect(item, SIGNAL(clicked(TimeZoneListItem*)),
                this, SLOT(itemClicked(TimeZoneListItem*)));

        if (!m_CheckedItem) {
            QString current = DcpTimeZoneConf::instance()->defaultTimeZone().city();
            if (item->city() == current) {
                item->checked(true);
                m_CheckedItem = item;
            }
        }
        count++;
        if (count == 40) {
            qApp->processEvents();
            break;
        }
    }

    // orientation change
    connect(DuiSceneManager::instance(), SIGNAL(orientationChanged(const Dui::Orientation &)),
            this, SLOT(orientationChanged()));

    int columnwidth = DuiSceneManager::instance()->visibleSceneSize(
                                              Dui::Landscape).width() / 2 - 25;
    m_MainLayoutPolicy->setColumnFixedWidth(0, columnwidth);
    // orientationChanged();
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
    if (m_CheckedItem) m_CheckedItem->checked(false);
    item->checked(true);
    m_CheckedItem = item;

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

void TimeZoneContainer::filter(const QString& sample)
{
    QListIterator<TimeZoneListItem*> iter(m_ItemList);
    while (iter.hasNext()) {
        TimeZoneListItem *item = iter.next();
        if (item->country().startsWith(sample, Qt::CaseInsensitive) ||
            item->city().startsWith(sample, Qt::CaseInsensitive)) {
            item->filtered(true);
        } else {
            item->filtered(false);
        }
    }

    updateLayout();
}

