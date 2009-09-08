#include "timezoneview.h"

#include "dcpdatetime.h"
#include "datetimetranslation.h"
#include "dcptable.h"
#include "dcptimezonedelegate.h"
#include "dcptimezonedata.h"
#include "dcptimezoneconf.h"

#include <duitextedit.h>
#include <QGraphicsLinearLayout>
#include <duipannableviewport.h>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <DuiSceneManager>

TimeZoneView::TimeZoneView(QGraphicsWidget *parent)
             :DcpWidget(parent)
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

    // pannable area:
    DuiPannableViewport* pannable = new DuiPannableViewport();
    layout->addItem(pannable);

    // model:
    QStandardItemModel* model = new QStandardItemModel(this);
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
        model->appendRow(item);
        zoneIter++;
    }
    QSortFilterProxyModel* filterModel = new QSortFilterProxyModel(this);
    filterModel->setSourceModel(model);
    filterModel->setFilterRole(DcpTimeZoneDelegate::TextRole1);

    // Table:
    m_Table = new DcpTable();
    m_Table->setDelegate(new DcpTimeZoneDelegate());
    m_Table->setModel(filterModel);
    pannable->setWidget(m_Table);
    QObject::connect (pannable,
           SIGNAL(sizePosChanged(const QSizeF&, const QRectF&, const QPointF&)),
           m_Table, SLOT(changeVisibleArea(const QSizeF&, const QRectF&,
                                           const QPointF&)));

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
    QSortFilterProxyModel* proxyModel =
        qobject_cast<QSortFilterProxyModel*>(m_Table->model());
    Q_ASSERT(proxyModel);
    proxyModel->setFilterRegExp(QRegExp(sample, Qt::CaseInsensitive,
                                             QRegExp::FixedString));
}

void TimeZoneView::orientationChanged()
{
    QSize size = DuiSceneManager::instance()->visibleSceneSize();
    setMinimumHeight(size.height()-60);
}


