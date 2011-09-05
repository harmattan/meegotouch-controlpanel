#include "dcpqmlgconfitem.h"

#include <MGConfItem>

DcpQmlGConfItem::DcpQmlGConfItem(QObject *parent) :
    QObject (parent),
    item(0)
{
    qmlRegisterType<DcpQmlGConfItem> (
            "com.nokia.controlpanel", 0, 1, "DcpQmlGConfItem"
    );
}

const QString 
DcpQmlGConfItem::key() const
{
    if(item)
    {
        return item->key();
    }
    
    return QString();
}
void 
DcpQmlGConfItem::setKey(const QString key)
{
    if(!item)
    {
        item = new MGConfItem(key);
        connect(item, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));
    }
}
const QString
DcpQmlGConfItem::value() const
{
    if(item)
    {
        return item->value().toString();
    }
}
void 
DcpQmlGConfItem::setValue(const QString value)
{
    if(item)
    {
        item->set(QVariant(value));
    }    
}
