#include <duigridlayoutpolicy.h>

/*
 * Fake GridLayoutPolicy.
 * It makes you able to launch the tests without X.
 *
 * ! It does not handle the list of items currently.
 * ! If you use this, you will also need to use duiabstractlayoutpolicy-fake.cpp
 */

DuiGridLayoutPolicy::DuiGridLayoutPolicy(DuiLayout* p): DuiAbstractLayoutPolicy(p){}
DuiGridLayoutPolicy::~DuiGridLayoutPolicy(){}
int DuiGridLayoutPolicy::rowCount() const{ return 0; }
int DuiGridLayoutPolicy::columnCount() const{ return 0; }
void DuiGridLayoutPolicy::setRowSpacing(int, qreal){}
qreal DuiGridLayoutPolicy::rowSpacing(int) const{return 0;}
void DuiGridLayoutPolicy::setColumnSpacing(int, qreal){}
qreal DuiGridLayoutPolicy::columnSpacing(int) const{ return 0;}
void DuiGridLayoutPolicy::setRowAlignment(int, Qt::Alignment){}
Qt::Alignment DuiGridLayoutPolicy::rowAlignment(int) const{ return Qt::AlignHCenter; }
void DuiGridLayoutPolicy::setColumnAlignment(int, Qt::Alignment){}
Qt::Alignment DuiGridLayoutPolicy::columnAlignment(int) const{ return Qt::AlignHCenter; }
QGraphicsLayoutItem* DuiGridLayoutPolicy::itemAt(int, int) const{ return 0; }
void DuiGridLayoutPolicy::addItem(QGraphicsLayoutItem*, int, int, int, int, Qt::Alignment){}
void DuiGridLayoutPolicy::removeAt(int){}
void DuiGridLayoutPolicy::setRowStretchFactor(int, int){}
int DuiGridLayoutPolicy::rowStretchFactor(int) const{ return 0; }
void DuiGridLayoutPolicy::setColumnStretchFactor(int, int){}
int DuiGridLayoutPolicy::columnStretchFactor(int) const{ return 0; }
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
void DuiGridLayoutPolicy::setHorizontalSpacing(qreal){}
void DuiGridLayoutPolicy::relayout(){}
void DuiGridLayoutPolicy::invalidate(){}

