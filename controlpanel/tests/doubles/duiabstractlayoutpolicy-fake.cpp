#include <duiabstractlayoutpolicy.h>
#include <QString>

DuiAbstractLayoutPolicy::DuiAbstractLayoutPolicy(DuiLayout*): d_ptr(0){}
DuiAbstractLayoutPolicy::~DuiAbstractLayoutPolicy(){}
void DuiAbstractLayoutPolicy::setContentsMargins(qreal, qreal, qreal, qreal){}
void DuiAbstractLayoutPolicy::unsetContentsMargins(){}
void DuiAbstractLayoutPolicy::getContentsMargins(qreal*, qreal*, qreal*, qreal*) const{}
DuiLayout* DuiAbstractLayoutPolicy::layout() const{ return 0; }
void DuiAbstractLayoutPolicy::activate(){}
bool DuiAbstractLayoutPolicy::isActive() const{ return false; }
QSizeF DuiAbstractLayoutPolicy::sizeHint(Qt::SizeHint, const QSizeF &) const{ return QSizeF(100,100); }
void DuiAbstractLayoutPolicy::updateStyle(){}
void DuiAbstractLayoutPolicy::setObjectName(const QString &){}
QString DuiAbstractLayoutPolicy::objectName() const{ return ""; }
void DuiAbstractLayoutPolicy::setHorizontalSpacing(qreal){}
qreal DuiAbstractLayoutPolicy::horizontalSpacing() const{ return 0; }
void DuiAbstractLayoutPolicy::setVerticalSpacing(qreal){}
qreal DuiAbstractLayoutPolicy::verticalSpacing() const{ return 0; }
void DuiAbstractLayoutPolicy::setSpacing(qreal){}
int DuiAbstractLayoutPolicy::count() const{ return 0; }
QGraphicsLayoutItem* DuiAbstractLayoutPolicy::itemAt(int) const{ return 0; }
int DuiAbstractLayoutPolicy::indexOf(const QGraphicsLayoutItem*) const{ return 0; }
void DuiAbstractLayoutPolicy::removeAt(int){}
void DuiAbstractLayoutPolicy::removeItem(const QGraphicsLayoutItem*){}
DuiAbstractLayoutPolicy::DuiAbstractLayoutPolicy(DuiAbstractLayoutPolicyPrivate &): d_ptr(0){}
void DuiAbstractLayoutPolicy::insertItem(int, QGraphicsLayoutItem*){}
void DuiAbstractLayoutPolicy::addItem(QGraphicsLayoutItem*){}
void DuiAbstractLayoutPolicy::setItemGeometry(int, const QRectF &){}
QRectF DuiAbstractLayoutPolicy::itemGeometry(int) const{ return QRectF(100,100,100,100); }
void DuiAbstractLayoutPolicy::hideItem(int){}
void DuiAbstractLayoutPolicy::applyStyle(){}
const DuiAbstractLayoutPolicyStyle* DuiAbstractLayoutPolicy::style() const{ return 0; }
void DuiAbstractLayoutPolicy::relayout(){}
void Q_DECL_DEPRECATED DuiAbstractLayoutPolicy::aboutToBeRemovedFromLayout(const QGraphicsLayoutItem*){}
void DuiAbstractLayoutPolicy::invalidatePolicyAndLayout(){}
void DuiAbstractLayoutPolicy::invalidate(){}
void DuiAbstractLayoutPolicy::updateGeometry(){}
QRectF DuiAbstractLayoutPolicy::contentsArea() const{ return QRectF(100,100,100,100); }
void DuiAbstractLayoutPolicy::activated(){}
