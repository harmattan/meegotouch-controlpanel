
#include "dcpdesktopentry.h"

#include <QStringList>

#include <QDebug>

DcpDesktopEntry::DcpDesktopEntry(const QString &fileName) : DuiDesktopEntry(fileName)
{

/* //debug information
    QStringList tmp = allKeys();

    QStringList::const_iterator constIterator;

    for (constIterator = tmp.constBegin(); constIterator != tmp.constEnd(); ++constIterator)
        qDebug() << (*constIterator).toLocal8Bit().constData() <<
                    value( (*constIterator).toLocal8Bit().constData() ).toString();
*/
}

QString DcpDesktopEntry::widgetType()
{
    return value("DCP/WidgetType", "").toString();
}

QString DcpDesktopEntry::text1()
{
    return value("DCP/Text1", "").toString();
}

QString DcpDesktopEntry::text2()
{
    return value("DCP/Text2", "").toString();
}

QString DcpDesktopEntry::image()
{
    return value("DCP/Image", "").toString();
}

QString DcpDesktopEntry::buttonCSS()
{
    return value("DCP/ButtonCSS", "").toString();
}

QString DcpDesktopEntry::label1CSS()
{
    return value("DCP/Label1CSS", "").toString();
}

QString DcpDesktopEntry::label2CSS()
{
    return value("DCP/Label2CSS", "").toString();
}

DcpDesktopEntry::~DcpDesktopEntry()
{

}


