#include <duilinearlayoutpolicy.h>

/* Fake Linear layout policy
 *
 * With this source you can fake the linear layout policy,
 * so it will only handle a list of items for you, and it will not require
 * you to use X for testing.
 *
 * ! If you use this, you will also need to use duiabstractlayoutpolicy-fake.cpp
 */

DuiLinearLayoutPolicy::DuiLinearLayoutPolicy(DuiLayout* p, Qt::Orientation):
    DuiAbstractLayoutPolicy(p)
{ }

DuiLinearLayoutPolicy::~DuiLinearLayoutPolicy(){}
qreal DuiLinearLayoutPolicy::spacing() const{ return 0; }
void DuiLinearLayoutPolicy::setSpacing(qreal){}
void DuiLinearLayoutPolicy::setItemSpacing(int, qreal){}
qreal DuiLinearLayoutPolicy::itemSpacing(int) const{ return 0; }
Qt::Orientation DuiLinearLayoutPolicy::orientation() const{ return Qt::Horizontal; }
void DuiLinearLayoutPolicy::setOrientation(Qt::Orientation){}

void DuiLinearLayoutPolicy::addItem(QGraphicsLayoutItem* item)
{
    DuiAbstractLayoutPolicy::addItem(item);
}

void DuiLinearLayoutPolicy::addItem(QGraphicsLayoutItem* item, Qt::Alignment)
{
    addItem(item);
}

void DuiLinearLayoutPolicy::insertItem(int pos, QGraphicsLayoutItem* item)
{
    DuiAbstractLayoutPolicy::insertItem(pos, item);
}

void DuiLinearLayoutPolicy::insertItem(int pos, QGraphicsLayoutItem* item,
                                       Qt::Alignment)
{
    insertItem(pos, item);
}

void DuiLinearLayoutPolicy::insertStretch(int, int){}
int DuiLinearLayoutPolicy::stretchFactor(QGraphicsLayoutItem*) const{ return 0; }
void DuiLinearLayoutPolicy::setStretchFactor(QGraphicsLayoutItem*, int){}
Qt::Alignment DuiLinearLayoutPolicy::alignment(QGraphicsLayoutItem*) const{ return Qt::AlignLeft; }
void DuiLinearLayoutPolicy::setAlignment(QGraphicsLayoutItem*, Qt::Alignment){}
QSizeF DuiLinearLayoutPolicy::sizeHint(Qt::SizeHint, const QSizeF &) const{ return QSizeF(100, 100); }
void DuiLinearLayoutPolicy::setHorizontalSpacing(qreal){}
void DuiLinearLayoutPolicy::setVerticalSpacing(qreal){}

void DuiLinearLayoutPolicy::removeAt(int pos)
{
    DuiAbstractLayoutPolicy::removeAt(pos);
}

void DuiLinearLayoutPolicy::relayout(){}
void DuiLinearLayoutPolicy::invalidate(){}

