#include "dcpqmlgconfitem.h"

#include <MGConfItem>

DcpQmlGConfItem::DcpQmlGConfItem (QObject *parent) :
    QObject (parent),
    m_Item (0)
{
}

const QString
DcpQmlGConfItem::key () const
{
    if (m_Item) {
        return m_Item->key ();
    }
    return QString ();
}

void
DcpQmlGConfItem::setKey (const QString& key)
{
    if (!m_Item) {
        m_Item = new MGConfItem (key);
        connect (m_Item, SIGNAL (valueChanged ()), this, SIGNAL (valueChanged ()));
        if (!m_Item->value().isValid() && !m_DefaultValue.isNull()) {
            setValue (m_DefaultValue);
        }
    }
}

const QString
DcpQmlGConfItem::value () const
{
    if (m_Item) {
        return m_Item->value ().toString ();
    }
    return QString();
}

void
DcpQmlGConfItem::setValue (const QString& value)
{
    if (m_Item) {
        m_Item->set (value);
    }
}

const QString
DcpQmlGConfItem::defaultValue () const
{
    return m_DefaultValue;
}

void
DcpQmlGConfItem::setDefaultValue (const QString& value)
{
    m_DefaultValue = value;
    if (m_Item && !m_Item->value().isValid()) {
        setValue (m_DefaultValue);
    }
}

