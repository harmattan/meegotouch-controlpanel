#include <duiabstractlayoutpolicy.h>
#include <QString>
#include <QList>

/* Fake abstract layout policy
 *
 * With this source you can fake the abstract layout policy,
 * so it will only handle a list of items for you, and it will not require
 * you to use X for testing.
 */

class DuiAbstractLayoutPolicyPrivate {
    public:
        QList<const QGraphicsLayoutItem*> items;
};

DuiAbstractLayoutPolicy::DuiAbstractLayoutPolicy(DuiLayout*):
    d_ptr(new DuiAbstractLayoutPolicyPrivate()) {}
DuiAbstractLayoutPolicy::DuiAbstractLayoutPolicy(
        DuiAbstractLayoutPolicyPrivate &p):
    d_ptr(&p)
{
}

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

int DuiAbstractLayoutPolicy::count() const
{
    return d_ptr->items.count();
}

QGraphicsLayoutItem* DuiAbstractLayoutPolicy::itemAt(int i) const
{
    return const_cast<QGraphicsLayoutItem*>(d_ptr->items.at(i));
}

int DuiAbstractLayoutPolicy::indexOf(const QGraphicsLayoutItem* item) const
{
    return d_ptr->items.indexOf(item);
}

void DuiAbstractLayoutPolicy::removeAt(int i)
{
    d_ptr->items.removeAt(i);
}

void DuiAbstractLayoutPolicy::removeItem(const QGraphicsLayoutItem* item)
{
    removeAt(indexOf(item));
}

void DuiAbstractLayoutPolicy::insertItem(int i, QGraphicsLayoutItem* item)
{
    d_ptr->items.insert(i, item);
}

void DuiAbstractLayoutPolicy::addItem(QGraphicsLayoutItem* item)
{
    d_ptr->items.append(item);
}

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

