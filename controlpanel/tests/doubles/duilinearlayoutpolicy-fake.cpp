#include <duilinearlayoutpolicy.h>

DuiLinearLayoutPolicy::DuiLinearLayoutPolicy(DuiLayout* p, Qt::Orientation): DuiAbstractLayoutPolicy(p){}
DuiLinearLayoutPolicy::~DuiLinearLayoutPolicy(){}
qreal DuiLinearLayoutPolicy::spacing() const{ return 0; }
void DuiLinearLayoutPolicy::setSpacing(qreal){}
void DuiLinearLayoutPolicy::setItemSpacing(int, qreal){}
qreal DuiLinearLayoutPolicy::itemSpacing(int) const{ return 0; }
Qt::Orientation DuiLinearLayoutPolicy::orientation() const{ return Qt::Horizontal; }
void DuiLinearLayoutPolicy::setOrientation(Qt::Orientation){}
void DuiLinearLayoutPolicy::addItem(QGraphicsLayoutItem*){}
void DuiLinearLayoutPolicy::addItem(QGraphicsLayoutItem*, Qt::Alignment){}
void DuiLinearLayoutPolicy::insertItem(int, QGraphicsLayoutItem*){}
void DuiLinearLayoutPolicy::insertItem(int, QGraphicsLayoutItem*, Qt::Alignment){}
void DuiLinearLayoutPolicy::insertStretch(int, int){}
int DuiLinearLayoutPolicy::stretchFactor(QGraphicsLayoutItem*) const{ return 0; }
void DuiLinearLayoutPolicy::setStretchFactor(QGraphicsLayoutItem*, int){}
Qt::Alignment DuiLinearLayoutPolicy::alignment(QGraphicsLayoutItem*) const{ return Qt::AlignLeft; }
void DuiLinearLayoutPolicy::setAlignment(QGraphicsLayoutItem*, Qt::Alignment){}
QSizeF DuiLinearLayoutPolicy::sizeHint(Qt::SizeHint, const QSizeF &) const{ return QSizeF(100, 100); }
void DuiLinearLayoutPolicy::setHorizontalSpacing(qreal){}
void DuiLinearLayoutPolicy::setVerticalSpacing(qreal){}
void DuiLinearLayoutPolicy::removeAt(int){}
void DuiLinearLayoutPolicy::relayout(){}
void DuiLinearLayoutPolicy::invalidate(){}

