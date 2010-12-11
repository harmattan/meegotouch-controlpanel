#include <MHelpButton>

MHelpButton::MHelpButton(const QString& pageID, QGraphicsItem* p)
{
    Q_UNUSED (pageID); // TODO
    Q_UNUSED (p);
}

QString MHelpButton::pageID() const
{
    return QString();
}

void MHelpButton::setPageID(const QString& id)
{
    Q_UNUSED (id);
}


