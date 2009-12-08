#ifndef DCPWRONGAPPLETS_H
#define DCPWRONGAPPLETS_H

#include <QSet>
#include <QHash>
#include <QString>

/** class is internal, handles wrong applet markings and queries */
class DcpWrongApplets
{
public:
    static inline DcpWrongApplets* instance();
    static inline void destroyInstance();

    void markAsMaybeBad(const QString& badSoPath);
    void unmarkAsMaybeBad(const QString& badSoPath);
    inline bool isBad(const QString& badSoPath);

private:
    DcpWrongApplets();
    static DcpWrongApplets* sm_Instance;

    // some speed up caches to avoid unnecessery gconf access
    QSet<QString> m_BadApplets;
    QHash<QString, int> m_MaybeBadApplets;
};

DcpWrongApplets* DcpWrongApplets::instance()
{
    if (!sm_Instance) sm_Instance = new DcpWrongApplets();
    return sm_Instance;
}

void DcpWrongApplets::destroyInstance()
{
    delete sm_Instance;
    sm_Instance = 0;
}

bool DcpWrongApplets::isBad(const QString& badSoName)
{
    return m_BadApplets.contains(badSoName);
}

//convenience methods:
void dcpMarkAsMaybeBad(const class DcpAppletMetadata* metadata);
void dcpUnmarkAsMaybeBad(const class DcpAppletMetadata* metadata);

#endif // DCPWRONGAPPLETS_H

