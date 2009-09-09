#ifndef DCPTABLE_H
#define DCPTABLE_H

#include <DuiWidget>
class DcpTableDelegate;
class QAbstractItemModel;
class QGraphicsSceneResizeEvent;
class QModelIndex;

class DcpTable: public DuiWidget
{
    Q_OBJECT

public:
    DcpTable(DuiWidget* parent = 0);
    virtual ~DcpTable();

    void setDelegate(DcpTableDelegate* delegate);
    void setModel(QAbstractItemModel* model);
    QAbstractItemModel* model();
    QSizeF sizeHint ( Qt::SizeHint which, const QSizeF & constraint = QSizeF() ) const;
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
    QModelIndex itemAt(const QPoint& point);

signals:
    void clicked ( const QModelIndex & index );

protected slots:
    void changeVisibleArea(const QSizeF & viewportSize,
                           const QRectF & pannedRange,
                           const QPointF & pannedPos);
    void updateGeometry();

protected:
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void polishEvent ();

private:
    void refreshDelegateWidth();
    DcpTableDelegate* m_Delegate;
    QAbstractItemModel* m_Model;
    QRectF m_VisibleArea;
};

inline QAbstractItemModel*
DcpTable::model()
{
    return m_Model;
}

#endif // DCPTABLE_H

