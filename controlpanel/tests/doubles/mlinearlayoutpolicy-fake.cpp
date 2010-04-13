#include <mlinearlayoutpolicy.h>

/* Fake Linear layout policy
 *
 * With this source you can fake the linear layout policy,
 * so it will only handle a list of items for you, and it will not require
 * you to use X for testing.
 *
 * ! If you use this, you will also need to use mabstractlayoutpolicy-fake.cpp
 */

MLinearLayoutPolicy::MLinearLayoutPolicy(MLayout* p, Qt::Orientation):
    MAbstractLayoutPolicy(p)
{ }

MLinearLayoutPolicy::~MLinearLayoutPolicy(){}
qreal MLinearLayoutPolicy::spacing() const{ return 0; }
void MLinearLayoutPolicy::setSpacing(qreal){}
void MLinearLayoutPolicy::setItemSpacing(int, qreal){}
qreal MLinearLayoutPolicy::itemSpacing(int) const{ return 0; }
Qt::Orientation MLinearLayoutPolicy::orientation() const{ return Qt::Horizontal; }
void MLinearLayoutPolicy::setOrientation(Qt::Orientation){}

void MLinearLayoutPolicy::addItem(QGraphicsLayoutItem* item)
{
    MAbstractLayoutPolicy::addItem(item);
}

void MLinearLayoutPolicy::addItem(QGraphicsLayoutItem* item, Qt::Alignment)
{
    addItem(item);
}

void MLinearLayoutPolicy::insertItem(int pos, QGraphicsLayoutItem* item)
{
    MAbstractLayoutPolicy::insertItem(pos, item);
}

void MLinearLayoutPolicy::insertItem(int pos, QGraphicsLayoutItem* item,
                                       Qt::Alignment)
{
    insertItem(pos, item);
}

void MLinearLayoutPolicy::insertStretch(int, int){}
int MLinearLayoutPolicy::stretchFactor(QGraphicsLayoutItem*) const{ return 0; }
void MLinearLayoutPolicy::setStretchFactor(QGraphicsLayoutItem*, int){}
Qt::Alignment MLinearLayoutPolicy::alignment(QGraphicsLayoutItem*) const{ return Qt::AlignLeft; }
void MLinearLayoutPolicy::setAlignment(QGraphicsLayoutItem*, Qt::Alignment){}
QSizeF MLinearLayoutPolicy::sizeHint(Qt::SizeHint, const QSizeF &) const{ return QSizeF(100, 100); }
void MLinearLayoutPolicy::setHorizontalSpacing(qreal){}
void MLinearLayoutPolicy::setVerticalSpacing(qreal){}

void MLinearLayoutPolicy::removeAt(int pos)
{
    MAbstractLayoutPolicy::removeAt(pos);
}

void MLinearLayoutPolicy::relayout(){}
void MLinearLayoutPolicy::invalidate(){}

