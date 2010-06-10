#include <QtGui>
#include <QDebug>
#include <MAction>
#include <MTheme>
#include <DcpWidget>
#include "buttonapplet.h"
#include "button.h"
#include "buttonbrief.h"

Q_EXPORT_PLUGIN2(buttonapplet, ButtonApplet)

void ButtonApplet::init()
{
    MTheme::loadCSS(DATADIR "/buttonapplet.css");
};

DcpWidget* ButtonApplet::constructWidget(int widgetId)
{
    Q_UNUSED(widgetId);
    return 0;
}

QString ButtonApplet::title() const
{
    return "";
}

QVector<MAction*> ButtonApplet::viewMenuItems()
{
    QVector<MAction*> vector(1);
    return vector;
}

DcpBrief* ButtonApplet::constructBrief(int)
{
    return new ButtonBrief();
}

