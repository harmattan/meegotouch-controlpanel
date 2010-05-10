#include <qgraphicslinearlayout.h>

#include <QList>
#include <QHash>

struct QGraphicsLinearLayoutFake
{
    QList<QGraphicsLayoutItem*> items;
};

static QHash<const QGraphicsLinearLayout*, QGraphicsLinearLayoutFake*> layouts;

QGraphicsLinearLayout::QGraphicsLinearLayout(QGraphicsLayoutItem* parent)
    : QGraphicsLayout(parent)
{
    layouts.insert(this, new QGraphicsLinearLayoutFake);
}

QGraphicsLinearLayout::QGraphicsLinearLayout(Qt::Orientation, QGraphicsLayoutItem* parent)
    : QGraphicsLayout(parent)
{
    layouts.insert(this, new QGraphicsLinearLayoutFake);
}

QGraphicsLinearLayout::~QGraphicsLinearLayout(){}
void QGraphicsLinearLayout::setOrientation(Qt::Orientation){}

Qt::Orientation QGraphicsLinearLayout::orientation() const
{
    return Qt::Horizontal;
}

// inline void addItem(QGraphicsLayoutItem* item){}

void QGraphicsLinearLayout::insertItem(int i, QGraphicsLayoutItem* item)
{
    layouts[this]->items.insert(i, item);
}

void QGraphicsLinearLayout::removeItem(QGraphicsLayoutItem* item)
{
    layouts[this]->items.removeOne(item);
}

void QGraphicsLinearLayout::removeAt(int index)
{
    layouts[this]->items.removeAt(index);
}

int QGraphicsLinearLayout::count() const
{
    return layouts[this]->items.count();
}

QGraphicsLayoutItem* QGraphicsLinearLayout::itemAt(int i) const
{
    return layouts[this]->items[i];
}

void QGraphicsLinearLayout::insertStretch(int, int) {}
void QGraphicsLinearLayout::setSpacing(qreal){}
qreal QGraphicsLinearLayout::spacing() const{ return 0.0f; }
void QGraphicsLinearLayout::setItemSpacing(int, qreal){}
qreal QGraphicsLinearLayout::itemSpacing(int) const{ return 0.0f; }
void QGraphicsLinearLayout::setStretchFactor(QGraphicsLayoutItem*, int){}
int QGraphicsLinearLayout::stretchFactor(QGraphicsLayoutItem*) const{ return 1; }
void QGraphicsLinearLayout::setAlignment(QGraphicsLayoutItem*, Qt::Alignment){}
Qt::Alignment QGraphicsLinearLayout::alignment(QGraphicsLayoutItem*) const
{
    return Qt::AlignLeft;
}
void QGraphicsLinearLayout::setGeometry(const QRectF &){}
void QGraphicsLinearLayout::invalidate(){}
QSizeF QGraphicsLinearLayout::sizeHint(Qt::SizeHint, const QSizeF &) const
{
    return QSizeF(100,100);
}

