#include "dcpwrongapplets.h"

#include "dcpappletmetadata.h"
#include <DuiGConfItem>
#include <QFileInfo>
#include <QDateTime>
#include <QtDebug>

DcpWrongApplets* DcpWrongApplets::sm_Instance = 0;

const QString keyPath = "/apps/duicontrolpanel/badplugins";

static inline QDateTime fileTimeStamp(const QString& path)
{
    return QFileInfo(path).lastModified();
}

static inline QDateTime crashTimeStamp(const QString& name)
{
    DuiGConfItem conf(keyPath + "/" + name);
    return QDateTime::fromString(conf.value().toString());
}

static inline void setCrashTimeStamp(const QString& name, const QDateTime& date)
{
    DuiGConfItem conf(keyPath + "/" + name);
    conf.set(date.toString()); // DuiGConfItem does not support
                               // storing a qdatetime yet, not even int :(
}

static inline void unsetCrashTimeStamp(const QString& name)
{
    DuiGConfItem conf(keyPath + "/" + name);
    conf.unset();
}

DcpWrongApplets::DcpWrongApplets()
{
    // init cache:
    DuiGConfItem dir(keyPath);
    QList<QString> wrongAppletNames = dir.listEntries();
    foreach (QString name, wrongAppletNames) {
        if (fileTimeStamp(APPLET_LIBS + name) == crashTimeStamp(name)) {
            m_BadApplets.insert(name);
            qDebug() << "XXX Detected bad applet: " << name;
        } else {
            unsetCrashTimeStamp(name);
            qDebug() << "XXX Giving the applet" << name << "another chance.";
        }
    }
}


void
DcpWrongApplets::markAsMaybeBad(const QString& badSoPath)
{
    // no .so -> no problem
    if (badSoPath.isEmpty()) return;

    QFileInfo fileInfo(badSoPath);
    QString badSoName = fileInfo.fileName();

    if (!m_MaybeBadApplets.contains(badSoName)
        || m_MaybeBadApplets.value(badSoName) == 0)
    {
        QDateTime timeStamp = fileTimeStamp(badSoPath);
        // .so does not exists -> no segfault can happen
        if (timeStamp.isNull()) {
            qWarning("Could not find .so: %s", qPrintable(badSoPath));
            return;
        }
        setCrashTimeStamp(badSoName, timeStamp);
        m_MaybeBadApplets.insert (badSoName, 1);
    } else {
        m_MaybeBadApplets[badSoName]++;
    }
}


void
DcpWrongApplets::unmarkAsMaybeBad(const QString& badSoPath)
{
    // no .so -> no problem
    if (badSoPath.isEmpty()) return;

    QString badSoName = QFileInfo(badSoPath).fileName();
    Q_ASSERT(m_MaybeBadApplets.contains(badSoName));
    int& markCount = m_MaybeBadApplets[badSoName];
    Q_ASSERT(markCount > 0);
    markCount--;

    if (markCount == 0) {
        // mark it as working
        DuiGConfItem conf(keyPath+"/"+badSoName);
        conf.unset();
    }
}

void dcpMarkAsMaybeBad (const DcpAppletMetadata* metadata)
{
    DcpWrongApplets::instance()->markAsMaybeBad (metadata->fullBinary());
}

void dcpUnmarkAsMaybeBad (const DcpAppletMetadata* metadata)
{
    DcpWrongApplets::instance()->unmarkAsMaybeBad (metadata->fullBinary());
}

