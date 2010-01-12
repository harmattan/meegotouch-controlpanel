#include "dcpdeclapplet.h"
#include <QDebug>
#include <DuiAction>
#include "dcpdeclwidget.h"
#include "dcpdeclbrief.h"

Q_EXPORT_PLUGIN2(declarative, DcpDeclApplet)

void DcpDeclApplet::init()
{
}

DcpWidget* DcpDeclApplet::constructWidget(int widgetId)
{
    if (widgetId >= 0 && widgetId < m_XmlPaths.count()) {
        return new DcpDeclWidget(m_XmlPaths.at(widgetId));
    } else {
        qWarning("declarative applet was called with non valid widgetid: %d",
                 widgetId);
        return 0;
    }
}


QString DcpDeclApplet::title() const
{
    return QString(); // TODO
}

QVector<DuiAction*> DcpDeclApplet::viewMenuItems()
{
    QVector<DuiAction*> vector;
    return vector;
}

DcpBrief* DcpDeclApplet::constructBrief(int)
{
    return new DcpDeclBrief(); // TODO
}

int DcpDeclApplet::partID(const QString& partStr)
{
    int id = m_XmlPaths.indexOf(partStr);
    if (id < 0){
        id = m_XmlPaths.count();
        m_XmlPaths.append(partStr);
    }
    return id;
}

