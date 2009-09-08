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
/*    connect (this, SIGNAL(orientationChanged (Dui::Orientation)),
             this, SLOT(onOrientationChange())); */
/*
    m_Model, SIGNAL(layoutChanged ())
rowsInserted ( const QModelIndex & parent, int start, int end )
rowsRemoved ( const QModelIndex & parent, int start, int end )
columnsInserted ( const QModelIndex & parent, int start, int end )
columnsRemoved ( const QModelIndex & parent, int start, int end )
dataChanged ( const QModelIndex & topLeft, const QModelIndex & bottomRight )
*/

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
    qDebug() << size;
    return size;
}

void
DcpTable::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (!m_Delegate || !m_Model) return;

    qreal itemHeight = m_Delegate->height();

    int min = m_VisibleArea.y() / itemHeight;
    int count = m_VisibleArea.height() / itemHeight + 1;

    Dui::Orientation orientation = DuiSceneManager::instance()->orientation();

    // set the start y position:
    painter->translate(0, min*itemHeight);

    if (orientation == Dui::Landscape) {
        min *= 2;
        count *= 2;
    }

    // paint the items until they are visible:
    int max = min + count;
    qDebug() << "painting from" << min << "to" << max;
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


