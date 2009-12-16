#include "dcpwrongapplets.h"

#include "dcpappletmetadata.h"
#include <DuiGConfItem>
#include <QFileInfo>
#include <QDateTime>
#include <QtDebug>

#include <QApplication>

DcpWrongApplets* DcpWrongApplets::sm_Instance = 0;
bool DcpWrongApplets::sm_Disabled = false;

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
    connect (qApp, SIGNAL(aboutToQuit()),
             this, SLOT(deleteLater()));

    // init cache:
    m_BadApplets = queryBadApplets();
}

QSet<QString> DcpWrongApplets::queryBadApplets()
{
    QSet<QString> badApplets;
    if (sm_Disabled) 
	    return badApplets;

    DuiGConfItem dir(keyPath);
    QList<QString> wrongAppletNames = dir.listEntries();
    foreach (QString fullName, wrongAppletNames) {
        QString name = QFileInfo(fullName).fileName();
        QString fileName = QString(APPLET_LIBS)+ "/"+ name;
        if (fileTimeStamp(fileName) == crashTimeStamp(name)) {
//            qDebug() << "Detected bad applet: " << name;
            badApplets.insert(name);
        } else {
            qDebug() << "Giving the applet" << name << "another chance.";
            unsetCrashTimeStamp(name);
        }
    }
    return badApplets;
}

DcpWrongApplets::~DcpWrongApplets()
{
    qDebug() << "Marking possibly bad applets as good";
    QHash<QString, int>::const_iterator it;
    for (it = m_MaybeBadApplets.begin(); it!=m_MaybeBadApplets.end(); it++)
    {
        if (it.value() > 0) {
            qWarning() << it.key() << "were not unmarked:" << it.value();
            unsetCrashTimeStamp(it.key());
        }
    }
}

void
DcpWrongApplets::markAsMaybeBad(const QString& badSoPath)
{
    // no .so -> no problem
    if (sm_Disabled || badSoPath.isEmpty()) return;

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
DcpWrongApplets::unmarkAsMaybeBad(
		const QString& badSoPath)
{
    // no .so -> no problem
    if (sm_Disabled || badSoPath.isEmpty()) 
	    return;

    QFileInfo fileInfo(badSoPath);
    QString badSoName = fileInfo.fileName();

    // prevent unmarking bad or non existing applets (no more trouble with them)
    if (m_BadApplets.contains(badSoName) || !fileInfo.exists()) return;

    int& markCount = m_MaybeBadApplets[badSoName];
    if (markCount <= 0) {
        qWarning("Not marked plugin was unmarked: %s", qPrintable(badSoName));
        return;
    }
    markCount--;

    if (markCount == 0) {
        // mark it as working
        DuiGConfItem conf(keyPath+"/"+badSoName);
        conf.unset();
    }
}

void
dcpMarkAsMaybeBad (
		const DcpAppletMetadata* metadata)
{
    DcpWrongApplets::instance()->markAsMaybeBad (metadata->fullBinary());
}

void 
dcpUnmarkAsMaybeBad (
		const DcpAppletMetadata* metadata)
{
    DcpWrongApplets::instance()->unmarkAsMaybeBad (metadata->fullBinary());
}

DcpWrongApplets *
DcpWrongApplets::instance()
{
    if (!sm_Instance) 
	    sm_Instance = new DcpWrongApplets();

    return sm_Instance;
}

void 
DcpWrongApplets::destroyInstance()
{
    if (sm_Instance) {
        delete sm_Instance;
        sm_Instance = 0;
    }
}


const QSet<QString> &
DcpWrongApplets::badApplets() const
{
    return m_BadApplets;
}


bool 
DcpWrongApplets::isBad (
		const QString& badSoName)
{
    return m_BadApplets.contains(QFileInfo(badSoName).fileName());
}


void DcpWrongApplets::disable ()
{
    sm_Disabled = true;
    destroyInstance();
}

