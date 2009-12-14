#include <QtGui>
#include <QDebug>
#include <DuiAction>
#include <DuiTheme>
#include <DcpWidget>
#include "dcpskeletonapplet.h"
#include "dcpskeletonwidget.h"
#include "dcpskeleton.h"
#include "translations.h"
#include "dcpskeletonbrief.h"

Q_EXPORT_PLUGIN2(skeletonapplet, SkeletonApplet)

void SkeletonApplet::init()
{
    DuiTheme::loadCSS(QString(CSSDIR) + "skeletonapplet.css");
};

DcpWidget* SkeletonApplet::constructWidget(int widgetId)
{
	switch (widgetId)
    {
        case DcpSkeleton::Main:
                    return pageMain();
                    break;
        // more cases here if applet has more pages
        default:
                    qDebug() << "Page Unknown";
                    return 0;
                    break;
    };
}

DcpWidget* SkeletonApplet::pageMain()
{
	return new SkeletonWidget();
}



QString SkeletonApplet::title() const
{
        return DcpSkeleton::AppletTitle;
}

QVector<DuiAction*> SkeletonApplet::viewMenuItems()
{
    QVector<DuiAction*> vector(1);
    vector[0] = new DuiAction("Help", this);
    vector[0]->setLocation(DuiAction::ApplicationMenu);
    return vector;
}

DcpBrief* SkeletonApplet::constructBrief(int)
{
    return new SkeletonBrief();
}

