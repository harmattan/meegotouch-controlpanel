#include <mgridlayoutpolicy.h>

/*
 * Fake GridLayoutPolicy.
 * It makes you able to launch the tests without X.
 *
 * ! It does not handle the list of items currently.
 * ! If you use this, you will also need to use mabstractlayoutpolicy-fake.cpp
 */
#include <QMap>
#include <QHash>
#include <QPair>

static QHash<const MGridLayoutPolicy*, MGridLayoutPolicyPrivate*> priv;

class MGridLayoutPolicyPrivate
{
public:
    QMap<QPair<int, int>, QGraphicsLayoutItem*> items;
    QMap<int, int> stretchFactors;
    QMap<int, qreal> rowSpacing;
    QMap<int, qreal> colSpacing;
};

MGridLayoutPolicy::MGridLayoutPolicy(MLayout* p)
    : MAbstractLayoutPolicy(p)
{
    priv[this] = new MGridLayoutPolicyPrivate;
}

MGridLayoutPolicy::~MGridLayoutPolicy(){}
int MGridLayoutPolicy::rowCount() const{ return 0; }
int MGridLayoutPolicy::columnCount() const
{
    return priv[this]->items.count(); // FALSE!! this is all of the items
}
void MGridLayoutPolicy::setRowSpacing(int row, qreal space)
{
    priv[this]->rowSpacing[row] = space;
}

qreal MGridLayoutPolicy::rowSpacing(int row) const
{
    return priv[this]->rowSpacing[row];
}

void MGridLayoutPolicy::setColumnSpacing(int column, qreal space)
{
    priv[this]->colSpacing[column] = space;
}

qreal MGridLayoutPolicy::columnSpacing(int column) const
{
    return priv[this]->colSpacing[column];
}

void MGridLayoutPolicy::setRowAlignment(int, Qt::Alignment){}
Qt::Alignment MGridLayoutPolicy::rowAlignment(int) const{ return Qt::AlignHCenter; }
void MGridLayoutPolicy::setColumnAlignment(int, Qt::Alignment){}
Qt::Alignment MGridLayoutPolicy::columnAlignment(int) const{ return Qt::AlignHCenter; }
QGraphicsLayoutItem* MGridLayoutPolicy::itemAt(int row, int col) const
{
    return priv[this]->items[QPair<int, int>(row, col)];
}
void MGridLayoutPolicy::addItem(QGraphicsLayoutItem* item, int row, int col, int, int, Qt::Alignment)
{
    QPair<int, int> key(row, col);
    //priv[this]->items[QPair<int, int>(row, col)] = item;
    priv[this]->items[key] = item;
}
void MGridLayoutPolicy::removeAt(int){}
void MGridLayoutPolicy::setRowStretchFactor(int, int){}
int MGridLayoutPolicy::rowStretchFactor(int) const{ return 0; }
void MGridLayoutPolicy::setColumnStretchFactor(int column, int factor)
{
    priv[this]->stretchFactors[column] = factor; 
}
int MGridLayoutPolicy::columnStretchFactor(int column) const
{
    return priv[this]->stretchFactors[column]; 
}
void MGridLayoutPolicy::setRowMinimumHeight(int, qreal){}
qreal MGridLayoutPolicy::rowMinimumHeight(int) const{ return 0; }
void MGridLayoutPolicy::setRowPreferredHeight(int, qreal){}
qreal MGridLayoutPolicy::rowPreferredHeight(int) const{ return 0; }
void MGridLayoutPolicy::setRowMaximumHeight(int, qreal){}
qreal MGridLayoutPolicy::rowMaximumHeight(int) const{ return 0; }
void MGridLayoutPolicy::setRowFixedHeight(int, qreal){}
void MGridLayoutPolicy::setColumnMinimumWidth(int, qreal){}
qreal MGridLayoutPolicy::columnMinimumWidth(int) const{ return 0; }
void MGridLayoutPolicy::setColumnPreferredWidth(int, qreal){}
qreal MGridLayoutPolicy::columnPreferredWidth(int) const{ return 0; }
void MGridLayoutPolicy::setColumnMaximumWidth(int, qreal){}
qreal MGridLayoutPolicy::columnMaximumWidth(int) const{ return 0; }
void MGridLayoutPolicy::setColumnFixedWidth(int, qreal){}
Qt::Alignment MGridLayoutPolicy::alignment(QGraphicsLayoutItem*) const{ return Qt::AlignHCenter; }
void MGridLayoutPolicy::setAlignment(QGraphicsLayoutItem*, Qt::Alignment){}
QSizeF MGridLayoutPolicy::sizeHint(Qt::SizeHint, const QSizeF &) const{ return QSizeF(100, 100); }
void MGridLayoutPolicy::relayout(){}
void MGridLayoutPolicy::invalidate(){}
void MGridLayoutPolicy::setHorizontalSpacing(qreal space)
{
    MAbstractLayoutPolicy::setHorizontalSpacing(space);
}

void MGridLayoutPolicy::setVerticalSpacing(qreal space)
{
    MAbstractLayoutPolicy::setVerticalSpacing(space);
}
