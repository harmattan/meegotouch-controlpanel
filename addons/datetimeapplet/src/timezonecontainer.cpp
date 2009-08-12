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

static const int FIRST_LOAD_COUNT = 20;
static const int COUNT_AFTER_PROCESSEVENTS = 5;

TimeZoneContainer::TimeZoneContainer(DuiWidget *parent)
                  :DuiWidget(parent),
                   m_CheckedItem(0),
                   m_BackPushed(false)
{
    initWidget();
}

TimeZoneContainer::~TimeZoneContainer()
{
}

void TimeZoneContainer::backPushed(bool pushed)
{
    m_BackPushed = pushed;
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
    QListIterator<TimeZoneListItem*> iter(m_ItemList);
    while (iter.hasNext()) {
        TimeZoneListItem *item = iter.next();
        item->setVisibleSeparator(true);
        addItemToPolicies(item);
    }
    orientationChanged();
}

void TimeZoneContainer::addItemToPolicies(TimeZoneListItem* item)
{
    if (item->isFiltered()) {
        int count = m_MainLayoutPolicy->count();
        m_MainLayoutPolicy->addItemAtPosition(item, count / 2, count % 2);
        m_MainVLayoutPolicy->addItemAtPosition(item, count++,
                                               Qt::AlignLeft | Qt::AlignVCenter);
        item->activate();
        item->setVisible(true);
        item->setVisibleSeparator(false);

        if (count % 2 == 1 && count > 2) {
            // makes separators of previous line visible:
            static_cast<TimeZoneListItem*>(
                    m_MainLayout->itemAt(count-2))->setVisibleSeparator(true);
            static_cast<TimeZoneListItem*>(
                    m_MainLayout->itemAt(count-3))->setVisibleSeparator(true);
        }
    }
}

void TimeZoneContainer::addMoreItems()
{
    // add items to m_ItemMap
    QMultiMap<QString, DcpTimeZoneData*> zoneMap = DcpTimeZoneConf::instance()->getMap();
    QMapIterator<QString, DcpTimeZoneData*> zoneIter(zoneMap);
    int count = -1;
    while (zoneIter.hasNext()) {
        if (m_BackPushed) {
            break;
        }
        zoneIter.next();
        count++;
        TimeZoneListItem *item = new TimeZoneListItem(zoneIter.value()->timeZone(),
                                                  zoneIter.value()->country(),
                                                  zoneIter.value()->gmt(),
                                                  zoneIter.value()->city(),
                                                  this);
        m_ItemList << item;

        connect(item, SIGNAL(clicked(TimeZoneListItem*)),
                this, SLOT(itemClicked(TimeZoneListItem*)));
        item->setVisible(false);

        if (!m_CheckedItem) {
            QString current = DcpTimeZoneConf::instance()->defaultTimeZone().city();
            if (item->city() == current) {
                item->checked(true);
                m_CheckedItem = item;
            }
        }

        checkIfFiltered(item);
        addItemToPolicies(item);

        if (count > FIRST_LOAD_COUNT && (count % COUNT_AFTER_PROCESSEVENTS == 0)) {
            qApp->processEvents();
        }
    }
    orientationChanged();
}

void TimeZoneContainer::checkIfFiltered(TimeZoneListItem* item)
{
     if (item->country().startsWith(m_FilterSample, Qt::CaseInsensitive) ||
         item->city().startsWith(m_FilterSample, Qt::CaseInsensitive)) {
         item->filtered(true);
     } else {
         item->filtered(false);
     }
}

void TimeZoneContainer::filter(const QString& sample)
{
    if (m_FilterSample == sample) return;
    m_FilterSample = sample;
    QListIterator<TimeZoneListItem*> iter(m_ItemList);
    while (iter.hasNext()) {
        TimeZoneListItem *item = iter.next();
        checkIfFiltered(item);
    }
    updateLayout();
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

    // orientation change
    connect(DuiSceneManager::instance(), SIGNAL(orientationChanged(const Dui::Orientation &)),
            this, SLOT(orientationChanged()));

    int columnwidth = DuiSceneManager::instance()->visibleSceneSize(
                                              Dui::Landscape).width() / 2 - 25;
    m_MainLayoutPolicy->setColumnFixedWidth(0, columnwidth);
}

void TimeZoneContainer::orientationChanged()
{
    DuiSceneManager *manager = DuiSceneManager::instance();
    if (manager == 0)
        return;

    switch (manager->orientation()) {
        case Dui::Landscape:
//            setMinimumWidth(manager->visibleSceneSize().width()-24);
            m_MainLayout->setPolicy(m_MainLayoutPolicy);
            updateGridSeparator();
            break;
        case Dui::Portrait:
//            setMinimumWidth(manager->visibleSceneSize().width()-24);
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

