#include "duilayout.h"

/* A fake duilayout
 *
 * Can be used to create tests which run without X.
 * It does nothing, handles nothing.
 *
 * If you use it, consider using one of the fake policies:
 * - duigridlayoutpolicy-fake.cpp
 * - duilinearlayoutpolicy-fake.cpp
 *
 */

#include <duiabstractlayoutpolicy.h>

class DuiLayoutPrivate
{
public:
    QList<DuiAbstractLayoutPolicy*> policies;
    DuiAbstractLayoutPolicy *portraitPolicy;
    DuiAbstractLayoutPolicy *landscapePolicy;
    DuiLayoutAnimation *animation;
};

DuiLayout::DuiLayout(QGraphicsLayoutItem *) :
    d_ptr(new DuiLayoutPrivate)
{
}

DuiLayout::~DuiLayout()
{
     delete d_ptr;
}

void DuiLayout::invalidate()
{
}

void DuiLayout::invalidateLayoutOnly()
{
}

int DuiLayout::count() const
{
    return 0;
}

bool DuiLayout::isEmpty() const
{
    return true;
}

QGraphicsLayoutItem *DuiLayout::itemAt(int) const
{
    return 0;
}

void DuiLayout::removeAt(int index)
{
    (void)takeAt(index);
}

QGraphicsLayoutItem *DuiLayout::takeAt(int)
{
    return 0;
}

void DuiLayout::animatedDeleteItem(const QGraphicsLayoutItem *const)
{
}

void DuiLayout::animatedDeleteAt(int)
{
}

QSizeF DuiLayout::sizeHint(Qt::SizeHint , const QSizeF &) const
{
    return QSizeF(-1, -1);
}

void DuiLayout::setGeometry(const QRectF &)
{
}

int DuiLayout::addItem(QGraphicsLayoutItem *)
{
    return 0;
}

void DuiLayout::removeItem(const QGraphicsLayoutItem *const item)
{
    // this is necessery, because the item removes itself from the
    // policies through the layout when it gets destroyed
    foreach (DuiAbstractLayoutPolicy* layout, d_ptr->policies) {
        layout->removeItem(item);
    }
}

int DuiLayout::indexOf(const QGraphicsItem *) const
{
    return -1;
}

int DuiLayout::indexOf(const QGraphicsLayoutItem *) const
{
    return -1;
}

void DuiLayout::setPolicy(DuiAbstractLayoutPolicy *)
{
}

void DuiLayout::setLandscapePolicy(DuiAbstractLayoutPolicy *policy)
{
    d_ptr->landscapePolicy = policy;
}

DuiAbstractLayoutPolicy *DuiLayout::landscapePolicy() const
{
    return d_ptr->landscapePolicy;
}

void DuiLayout::setPortraitPolicy(DuiAbstractLayoutPolicy *policy)
{
    d_ptr->portraitPolicy = policy;
}

DuiAbstractLayoutPolicy *DuiLayout::portraitPolicy() const
{
    return d_ptr->portraitPolicy;
}

DuiAbstractLayoutPolicy *DuiLayout::policy() const
{
    return 0;
}

QList<DuiAbstractLayoutPolicy *> DuiLayout::registeredPolicies() const
{
    return d_ptr->policies;
}

void DuiLayout::setAnimation(DuiLayoutAnimation *animation)
{
    d_ptr->animation = animation;
}

DuiLayoutAnimation *DuiLayout::animation() const
{
    return d_ptr->animation;
}

void DuiLayout::setContentsMargins(qreal, qreal, qreal, qreal)
{
}

void DuiLayout::getContentsMargins(qreal *, qreal *, qreal *, qreal *) const
{
}

Qt::LayoutDirection DuiLayout::layoutDirection() const
{
    return (Qt::LayoutDirection) 0;
}
void DuiLayout::widgetEvent ( QEvent * )
{
}
