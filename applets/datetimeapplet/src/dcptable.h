#ifndef DCPTABLE_H
#define DCPTABLE_H

#include <DuiWidget>
class DcpTableDelegate;
class QAbstractItemModel;
class QGraphicsSceneResizeEvent;

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

public slots:
    void changeVisibleArea(const QSizeF & viewportSize,
                           const QRectF & pannedRange,
                           const QPointF & pannedPos);

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
