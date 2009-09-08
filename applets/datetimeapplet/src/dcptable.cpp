#include "dcptable.h"

#include "dcptabledelegate.h"
#include <QAbstractItemModel>
#include <QtDebug>

#include <DuiSceneManager>

DcpTable::DcpTable(DuiWidget* parent):
    DuiWidget(parent),
    m_Delegate(0),
    m_Model(0)
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

DcpTable::~DcpTable()
{
    if (m_Delegate) m_Delegate->deleteLater();
    if (m_Model) m_Model->deleteLater();
}


void
DcpTable::setDelegate(DcpTableDelegate* delegate)
{
    if (m_Delegate == delegate) return;

    if (m_Delegate) m_Delegate->deleteLater();
    m_Delegate = delegate;
    updateGeometry();
}

void
DcpTable::setModel(QAbstractItemModel* model)
{
    if (m_Model == model) return;

    if (m_Model) m_Model->deleteLater();
    m_Model = model;
/*    connect (m_Model, SIGNAL(layoutChanged ()), this, SLOT(update()));
    connect (m_Model, SIGNAL(columnsInserted ( const QModelIndex &, int, int)),
    connect (m_Model, SIGNAL(columnsRemoved ( const QModelIndex &, int , int )),
    connect (m_Model, SIGNAL(dataChanged ( const QModelIndex &, const QModelIndex & )),
    */

    // update the widget size when model changes itemcount:
    connect (m_Model, SIGNAL(rowsInserted ( const QModelIndex &, int, int)),
             this, SLOT(updateGeometry()));
    connect (m_Model, SIGNAL(rowsRemoved ( const QModelIndex &, int, int)),
             this, SLOT(updateGeometry()));

    updateGeometry(); // updates size
}

void
DcpTable::changeVisibleArea(const QSizeF & viewportSize,
                           const QRectF & pannedRange,
                           const QPointF & pannedPos)
{
    Q_UNUSED(pannedRange);
    m_VisibleArea = QRectF(pannedPos, viewportSize);
    refreshDelegateWidth();
}

void
DcpTable::refreshDelegateWidth()
{
    if (m_Delegate) {
        int width = size().width();
        if (DuiSceneManager::instance()->orientation() == Dui::Landscape){
            width /= 2;
        }
        m_Delegate->setWidth(width);
    }
}

QSizeF DcpTable::sizeHint ( Qt::SizeHint which, const QSizeF & constraint ) const
{
    Q_UNUSED(which);
    Q_UNUSED(constraint);

    QSizeF size;
    if (m_Model && m_Delegate){
        size = QSizeF(-1, m_Model->rowCount()*m_Delegate->height());
    }
    return size;
}

void
DcpTable::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (!m_Delegate || !m_Model) return;

    qreal itemHeight = m_Delegate->height();

    int min = qMax<int>(m_VisibleArea.y() / itemHeight, 0);
    int max = qMin<int>(m_VisibleArea.bottom() / itemHeight + 1, m_Model->rowCount());

    Dui::Orientation orientation = DuiSceneManager::instance()->orientation();

    // set the start y position:
    painter->translate(0, min*itemHeight);

    if (orientation == Dui::Landscape) {
        min *= 2;
        max = qMin(2*max, m_Model->rowCount());
    }

    // paint the items until they are visible:
    for (int row = min; row<max; row++){
        m_Delegate->paint(painter, m_Model->index(row,0));

        if (orientation == Dui::Landscape && row < max) {
            painter->translate(m_Delegate->width(),0);
            m_Delegate->paint(painter, m_Model->index(++row,0));
            painter->translate(-m_Delegate->width(),0);
        }

        painter->translate(0, itemHeight);
    }
}


void
DcpTable::updateGeometry()
{
    DuiWidget::updateGeometry();
}

QModelIndex
DcpTable::itemAt(const QPoint& point)
{
    int row = point.y() / m_Delegate->height();
    int column = point.x() / m_Delegate->width();
    if (DuiSceneManager::instance()->orientation() == Dui::Portrait) {
        return m_Model->index(row,0);
    } else {
        return m_Model->index(row*2+column, 0);
    }
}

void
DcpTable::mousePressEvent ( QMouseEvent * event )
{
    QModelIndex clickedItem = itemAt(event->pos());
    qDebug() << "XXX" << event->pos() << clickedItem;
    if (clickedItem.isValid()) {
        emit clicked(clickedItem);
    }
}

