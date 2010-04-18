#include <MContainer>
#include <QHash>
class MContainerPrivate
{
public:
    QGraphicsWidget *m_CentralWidget;
};

static QHash<MContainer*, MContainerPrivate*> priv;

MContainer::MContainer(QGraphicsItem *parent) 
{
    Q_UNUSED(parent);
    priv[this] = new MContainerPrivate;
}

MContainer::MContainer(const QString &title, QGraphicsItem *parent)
{
    Q_UNUSED(parent);
    Q_UNUSED(title);
}

MContainer::~MContainer()
{
}

QGraphicsWidget *MContainer::centralWidget()
{
    return priv[this]->m_CentralWidget;
}

void MContainer::setCentralWidget(QGraphicsWidget *centralWidget, bool destroy)
{
    priv[this]->m_CentralWidget = centralWidget;
    Q_UNUSED(destroy);

}

QString MContainer::title() const
{
    return "";
}

void MContainer::setTitle(const QString &newTitle)
{
    Q_UNUSED(newTitle);
}

QString MContainer::text() const
{
    return "";
}

void MContainer::setText(const QString &text)
{
    Q_UNUSED(text);
}

QString MContainer::iconID() const
{
    return "";
}

void MContainer::setIconID(const QString &iconID)
{
    Q_UNUSED(iconID);
}

bool MContainer::headerVisible() const
{
    return true;
}

void MContainer::setHeaderVisible(const bool visibility)
{
    Q_UNUSED(visibility);
}

void MContainer::toggleHeaderVisible()
{
}

bool MContainer::isProgressIndicatorVisible() const
{
    return false;
}

void MContainer::setProgressIndicatorVisible(bool visibility)
{
    Q_UNUSED(visibility);
}

void MContainer::toggleProgressIndicatorVisible()
{
}
