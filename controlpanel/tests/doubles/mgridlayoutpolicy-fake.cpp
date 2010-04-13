#include <mgridlayoutpolicy.h>

/*
 * Fake GridLayoutPolicy.
 * It makes you able to launch the tests without X.
 *
 * ! It does not handle the list of items currently.
 * ! If you use this, you will also need to use mabstractlayoutpolicy-fake.cpp
 */

MGridLayoutPolicy::MGridLayoutPolicy(MLayout* p): MAbstractLayoutPolicy(p){}
MGridLayoutPolicy::~MGridLayoutPolicy(){}
int MGridLayoutPolicy::rowCount() const{ return 0; }
int MGridLayoutPolicy::columnCount() const{ return 0; }
void MGridLayoutPolicy::setRowSpacing(int, qreal){}
qreal MGridLayoutPolicy::rowSpacing(int) const{return 0;}
void MGridLayoutPolicy::setColumnSpacing(int, qreal){}
qreal MGridLayoutPolicy::columnSpacing(int) const{ return 0;}
void MGridLayoutPolicy::setRowAlignment(int, Qt::Alignment){}
Qt::Alignment MGridLayoutPolicy::rowAlignment(int) const{ return Qt::AlignHCenter; }
void MGridLayoutPolicy::setColumnAlignment(int, Qt::Alignment){}
Qt::Alignment MGridLayoutPolicy::columnAlignment(int) const{ return Qt::AlignHCenter; }
QGraphicsLayoutItem* MGridLayoutPolicy::itemAt(int, int) const{ return 0; }
void MGridLayoutPolicy::addItem(QGraphicsLayoutItem*, int, int, int, int, Qt::Alignment){}
void MGridLayoutPolicy::removeAt(int){}
void MGridLayoutPolicy::setRowStretchFactor(int, int){}
int MGridLayoutPolicy::rowStretchFactor(int) const{ return 0; }
void MGridLayoutPolicy::setColumnStretchFactor(int, int){}
int MGridLayoutPolicy::columnStretchFactor(int) const{ return 0; }
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
void MGridLayoutPolicy::setHorizontalSpacing(qreal){}
void MGridLayoutPolicy::relayout(){}
void MGridLayoutPolicy::invalidate(){}

