#ifdef USE_USERGUIDE
#include <HelpButton>

HelpButton::HelpButton(const QString& pageID, QGraphicsItem* p)
{
    Q_UNUSED (pageID); // TODO
    Q_UNUSED (p);
}

QString HelpButton::pageID() const
{
    return QString();
}

void HelpButton::setPageID(const QString& id)
{
    Q_UNUSED (id);
}

void HelpButton::onClicked()
{
}

#endif // USE_USERGUIDE

