#include <duigridlayoutpolicy.h>

/*
 * Fake GridLayoutPolicy.
 * It makes you able to launch the tests without X.
 *
 * ! It does not handle the list of items currently.
 * ! If you use this, you will also need to use duiabstractlayoutpolicy-fake.cpp
 */
#include <QMap>
#include <QHash>
#include <QPair>

static QHash<const DuiGridLayoutPolicy*, DuiGridLayoutPolicyPrivate*> priv;

class DuiGridLayoutPolicyPrivate
{
public:
    QMap<QPair<int, int>, QGraphicsLayoutItem*> items;
    QMap<int, int> stretchFactors;
    QMap<int, qreal> rowSpacing;
    QMap<int, qreal> colSpacing;
};

DuiGridLayoutPolicy::DuiGridLayoutPolicy(DuiLayout* p)
    : DuiAbstractLayoutPolicy(p)
{
    priv[this] = new DuiGridLayoutPolicyPrivate;
}

DuiGridLayoutPolicy::~DuiGridLayoutPolicy(){}
int DuiGridLayoutPolicy::rowCount() const{ return 0; }
int DuiGridLayoutPolicy::columnCount() const{ return 0; }
void DuiGridLayoutPolicy::setRowSpacing(int row, qreal space)
{
    priv[this]->rowSpacing[row] = space;
}

qreal DuiGridLayoutPolicy::rowSpacing(int row) const
{
    return priv[this]->rowSpacing[row];
}

void DuiGridLayoutPolicy::setColumnSpacing(int column, qreal space)
{
    priv[this]->colSpacing[column] = space;
}

qreal DuiGridLayoutPolicy::columnSpacing(int column) const
{
    return priv[this]->colSpacing[column];
}

void DuiGridLayoutPolicy::setRowAlignment(int, Qt::Alignment){}
Qt::Alignment DuiGridLayoutPolicy::rowAlignment(int) const{ return Qt::AlignHCenter; }
void DuiGridLayoutPolicy::setColumnAlignment(int, Qt::Alignment){}
Qt::Alignment DuiGridLayoutPolicy::columnAlignment(int) const{ return Qt::AlignHCenter; }
QGraphicsLayoutItem* DuiGridLayoutPolicy::itemAt(int row, int col) const
{
    return priv[this]->items[QPair<int, int>(row, col)];
}
void DuiGridLayoutPolicy::addItem(QGraphicsLayoutItem* item, int row, int col, int, int, Qt::Alignment)
{
    QPair<int, int> key(row, col);
    //priv[this]->items[QPair<int, int>(row, col)] = item;
    priv[this]->items[key] = item;
}
void DuiGridLayoutPolicy::removeAt(int){}
void DuiGridLayoutPolicy::setRowStretchFactor(int, int){}
int DuiGridLayoutPolicy::rowStretchFactor(int) const{ return 0; }
void DuiGridLayoutPolicy::setColumnStretchFactor(int column, int factor)
{
    priv[this]->stretchFactors[column] = factor; 
}
int DuiGridLayoutPolicy::columnStretchFactor(int column) const
{
    return priv[this]->stretchFactors[column]; 
}
void DuiGridLayoutPolicy::setRowMinimumHeight(int, qreal){}
qreal DuiGridLayoutPolicy::rowMinimumHeight(int) const{ return 0; }
void DuiGridLayoutPolicy::setRowPreferredHeight(int, qreal){}
qreal DuiGridLayoutPolicy::rowPreferredHeight(int) const{ return 0; }
void DuiGridLayoutPolicy::setRowMaximumHeight(int, qreal){}
qreal DuiGridLayoutPolicy::rowMaximumHeight(int) const{ return 0; }
void DuiGridLayoutPolicy::setRowFixedHeight(int, qreal){}
void DuiGridLayoutPolicy::setColumnMinimumWidth(int, qreal){}
qreal DuiGridLayoutPolicy::columnMinimumWidth(int) const{ return 0; }
void DuiGridLayoutPolicy::setColumnPreferredWidth(int, qreal){}
qreal DuiGridLayoutPolicy::columnPreferredWidth(int) const{ return 0; }
void DuiGridLayoutPolicy::setColumnMaximumWidth(int, qreal){}
qreal DuiGridLayoutPolicy::columnMaximumWidth(int) const{ return 0; }
void DuiGridLayoutPolicy::setColumnFixedWidth(int, qreal){}
Qt::Alignment DuiGridLayoutPolicy::alignment(QGraphicsLayoutItem*) const{ return Qt::AlignHCenter; }
void DuiGridLayoutPolicy::setAlignment(QGraphicsLayoutItem*, Qt::Alignment){}
QSizeF DuiGridLayoutPolicy::sizeHint(Qt::SizeHint, const QSizeF &) const{ return QSizeF(100, 100); }
void DuiGridLayoutPolicy::relayout(){}
void DuiGridLayoutPolicy::invalidate(){}
void DuiGridLayoutPolicy::setHorizontalSpacing(qreal space)
{
    DuiAbstractLayoutPolicy::setHorizontalSpacing(space);
}

void DuiGridLayoutPolicy::setVerticalSpacing(qreal space)
{
    DuiAbstractLayoutPolicy::setVerticalSpacing(space);
}
