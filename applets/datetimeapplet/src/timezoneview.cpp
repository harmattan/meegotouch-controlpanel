#include "timezoneview.h"

#include "dcpdatetime.h"
#include "datetimetranslation.h"
#include "dcptable.h"
#include "dcptimezonedelegate.h"
#include "dcptimezonedata.h"
#include "dcptimezoneconf.h"

#include <duitextedit.h>
#include <QGraphicsLinearLayout>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <DuiSceneManager>
#include <QModelIndex>

TimeZoneView::TimeZoneView(QGraphicsWidget *parent)
             :DcpWidget(parent),
              m_SelectedItem(-1)
{
    setReferer(DcpDateTime::Main);
    initWidget();
}

TimeZoneView::~TimeZoneView()
{
}

void TimeZoneView::initWidget()
{
    // mainLayout
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(Qt::Vertical, this);

    // m_TextEdit
    m_TextEdit = new DuiTextEdit(DuiTextEditModel::SingleLine,
                                 DcpDateTime::InputCountryText,
                                 this);
    m_TextEdit->setObjectName("InputTextEdit");
    m_TextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(m_TextEdit, SIGNAL(gainedFocus(DuiTextEdit *, Qt::FocusReason)),
            this, SLOT(clearTextEdit(DuiTextEdit *)));
    connect(m_TextEdit, SIGNAL(textChanged()), this, SLOT(filteringListItems()));
    layout->addItem(m_TextEdit);

    // model:
    m_FullModel = new QStandardItemModel(this);
    // TODO XXX: this has to be optimized, a lot of copying
    QMultiMap<QString, DcpTimeZoneData*> zoneMap =
                                         DcpTimeZoneConf::instance()->getMap();
    QMultiMap<QString, DcpTimeZoneData*>::ConstIterator zoneIter =
                                         zoneMap.constBegin();
    QString defaultCity = DcpTimeZoneConf::instance()->defaultTimeZone().city();
    while (zoneIter != zoneMap.constEnd()) {
        DcpTimeZoneData* tz = zoneIter.value();

        QStandardItem* item = new QStandardItem();
        item->setData(tz->city(), DcpTimeZoneDelegate::TextRole1);
        item->setData(tz->gmt() + " " + tz->city(),
                      DcpTimeZoneDelegate::TextRole2);
        if (tz->city() == defaultCity){
            item->setData(false, DcpTimeZoneDelegate::NotCheckedRole);
        }
        m_FullModel->appendRow(item);
        zoneIter++;
    }
    QSortFilterProxyModel* filterModel = new QSortFilterProxyModel(this);
    filterModel->setSourceModel(m_FullModel);
    filterModel->setFilterRole(DcpTimeZoneDelegate::TextRole1);

    // Table:
    m_Table = new DcpTable();
    m_Table->setDelegate(new DcpTimeZoneDelegate());
    m_Table->setModel(filterModel);
    connect (m_Table, SIGNAL(clicked ( const QModelIndex &)),
             this, SLOT(onItemClicked( const QModelIndex &)));
    layout->addItem(m_Table);

    // handle orientation
    connect(DuiSceneManager::instance(),
            SIGNAL(orientationChanged(const Dui::Orientation &)),
            this, SLOT(orientationChanged()));
    orientationChanged();
}


void TimeZoneView::clearTextEdit(DuiTextEdit *textEdit)
{
    if (textEdit->text() == DcpDateTime::InputCountryText) {
        textEdit->setText("");
    }
}

void TimeZoneView::filteringListItems()
{
    QString sample = m_TextEdit->text();
    if (sample == DcpDateTime::InputCountryText)
        sample = "";
    proxyModel()->setFilterRegExp(QRegExp(sample, Qt::CaseInsensitive,
                                             QRegExp::FixedString));
}

QSortFilterProxyModel*
TimeZoneView::proxyModel()
{
    QSortFilterProxyModel* proxyModel =
        qobject_cast<QSortFilterProxyModel*>(m_Table->model());
    Q_ASSERT(proxyModel);
    return proxyModel;
}

void TimeZoneView::orientationChanged()
{
    QSize size = DuiSceneManager::instance()->visibleSceneSize();
    setMinimumHeight(size.height()-60);
}


void
TimeZoneView::onItemClicked( const QModelIndex &index)
{
    if (m_SelectedItem != -1) {
        selectItem(m_SelectedItem, false);
    }
    m_SelectedItem = proxyModel()->mapToSource(index).row();
    if (m_SelectedItem != -1) {
        selectItem(m_SelectedItem);
    }
}

void
TimeZoneView::selectItem(int item, bool selected)
{
    qDebug("select item: %d",item);
    m_FullModel->setData( m_FullModel->index(item, 0),
                          !selected, DcpTimeZoneDelegate::NotCheckedRole);
}

