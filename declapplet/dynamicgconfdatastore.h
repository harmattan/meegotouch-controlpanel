#ifndef DYNAMICGCONFDATASTORE_H
#define DYNAMICGCONFDATASTORE_H

#include <MDataStore>
#include <QHash>
class MGConfItem;

/*! @brief Dynamic gconf datastore
 *
 * Similar to MGConfDataStore, but that one only watches all key in one
 * directory. Instead this can watch all keys, but only those, whose value
 * was requested at least once.
 */
class DynamicGConfDataStore: public MDataStore
{
    Q_OBJECT

public:
    DynamicGConfDataStore(QObject* parent = 0);
    virtual ~DynamicGConfDataStore ();
    virtual QVariant value (const QString &key) const;
    virtual bool setValue (const QString &key, const QVariant &value);
    virtual QStringList allKeys () const;
    virtual bool contains (const QString &key) const;
    virtual bool createValue (const QString &key, const QVariant &value);
    virtual void remove (const QString &key);
    virtual void clear ();

signals:
    void valueChanged (const QString &key, const QVariant &value);

protected slots:
    void gconfValueChanged();

private:
    void ensureKeyInit (const QString& key);
    QHash<QString, MGConfItem*> m_GConf;
};


#endif // DYNAMICGCONFDATASTORE_H
