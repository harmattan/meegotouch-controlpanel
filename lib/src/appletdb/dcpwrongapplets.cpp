#include "dcpwrongapplets.h"

#include "dcpappletmetadata.h"
#include <DuiGConfItem>
#include <QFileInfo>
#include <QDateTime>
#include <QtDebug>

DcpWrongApplets* DcpWrongApplets::sm_Instance = 0;

const QString keyPath = "/apps/duicontrolpanel/badplugins";

static inline QString fileTimeStamp(const QString& path)
{
    return QFileInfo(path).lastModified().toString();
}

static inline QString crashTimeStamp(const QString& name)
{
    DuiGConfItem conf(keyPath + "/" + name);
    return conf.value().toString();
}

static inline void setCrashTimeStamp(const QString& name, const QString& date)
{
    DuiGConfItem conf(keyPath + "/" + name);
    conf.set(date);
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
    foreach (QString fullName, wrongAppletNames) {
        QString name = QFileInfo(fullName).fileName();
        QString fileName = QString(APPLET_LIBS)+ "/"+ name;
        if (fileTimeStamp(fileName) == crashTimeStamp(name)) {
            qDebug() << "!!! Detected bad applet: " << name;
            m_BadApplets.insert(name);
        } else {
            qDebug() << "Giving the applet" << name << "another chance.";
            unsetCrashTimeStamp(name);
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

    // prevent marking bad or non existing applets (no more trouble with them)
    if (m_BadApplets.contains(badSoName) || !fileInfo.exists()) return;

    if (!m_MaybeBadApplets.contains(badSoName)
        || m_MaybeBadApplets.value(badSoName) == 0)
    {
        QString timeStamp = fileTimeStamp(badSoPath);
        // .so does not exists -> no segfault can happen
        if (timeStamp.isEmpty()) {
            qWarning("Error getting timestamp: %s", qPrintable(badSoPath));
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

    QFileInfo fileInfo(badSoPath);
    QString badSoName = fileInfo.fileName();

    // prevent unmarking bad or non existing applets (no more trouble with them)
    if (m_BadApplets.contains(badSoName) || !fileInfo.exists()) return;

    int& markCount = m_MaybeBadApplets[badSoName];
    if (markCount <= 0) {
        qWarning("XXX Not marked plugin was unmarked: %s", qPrintable(badSoName));
        return;
    }
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


const QSet<QString>& DcpWrongApplets::badApplets() const
{
    return m_BadApplets;
}


bool DcpWrongApplets::isBad(const QString& badSoName)
{
    return m_BadApplets.contains(QFileInfo(badSoName).fileName());
}


