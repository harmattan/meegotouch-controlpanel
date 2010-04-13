#include "duilayout.h"

class DuiLayoutFake
{
public:
    DuiAbstractLayoutPolicy *portraitPolicy;
    DuiAbstractLayoutPolicy *landscapePolicy;
    DuiLayoutAnimation *animation;
};

DuiLayoutFake f;

DuiLayout::DuiLayout(QGraphicsLayoutItem *) :
    d_ptr(0)
{
}

DuiLayout::~DuiLayout()
{
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

void DuiLayout::removeItem(const QGraphicsLayoutItem *const)
{
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
    f.landscapePolicy = policy;
}

DuiAbstractLayoutPolicy *DuiLayout::landscapePolicy() const
{
    return f.landscapePolicy;
}

void DuiLayout::setPortraitPolicy(DuiAbstractLayoutPolicy *policy)
{
    f.portraitPolicy = policy;
}

DuiAbstractLayoutPolicy *DuiLayout::portraitPolicy() const
{
    return f.portraitPolicy;
}

DuiAbstractLayoutPolicy *DuiLayout::policy() const
{
    return 0;
}

QList<DuiAbstractLayoutPolicy *> DuiLayout::registeredPolicies() const
{
    return QList<DuiAbstractLayoutPolicy *>();
}

void DuiLayout::setAnimation(DuiLayoutAnimation *animation)
{
    f.animation = animation;
}

DuiLayoutAnimation *DuiLayout::animation() const
{
    return f.animation;
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
