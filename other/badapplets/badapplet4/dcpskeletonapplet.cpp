#include <QtGui>
#include <QDebug>
#include <DuiAction>
#include <DuiTheme>
#include <DcpWidget>
#include "dcpskeletonapplet.h"
#include "dcpskeletonwidget.h"
#include "dcpskeleton.h"
#include "dcpskeletonbrief.h"

Q_EXPORT_PLUGIN2(skeletonapplet, SkeletonApplet)

void SkeletonApplet::init()
{
    DuiTheme::loadCSS(QString(CSSDIR) + "skeletonapplet.css");
}

DcpWidget* SkeletonApplet::pageMain()
{
    return new SkeletonWidget();
}



QString SkeletonApplet::title() const
{
    return "AppletTitle";
}

QVector<DuiAction*> SkeletonApplet::viewMenuItems()
{
    QVector<DuiAction*> vector(1);
    vector[0] = new DuiAction("Help", this);
    vector[0]->setLocation(DuiAction::ApplicationMenuLocation);
    return vector;
}

DcpBrief* SkeletonApplet::constructBrief(int)
{
    return new SkeletonBrief();
}

