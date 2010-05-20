#include <QtGui>
#include <QDebug>
#include <MAction>
#include <MTheme>
#include <DcpWidget>
#include "dcpskeletonapplet.h"
#include "dcpskeletonwidget.h"
#include "dcpskeleton.h"
#include "dcpskeletonbrief.h"

Q_EXPORT_PLUGIN2(skeletonapplet, SkeletonApplet)

void SkeletonApplet::init()
{
    MTheme::loadCSS(QString(CSSDIR) + "skeletonapplet.css");
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
    //% "Skeleton applet"
    return qtTrId("dcp_skel_appl_titl");
}

QVector<MAction*> SkeletonApplet::viewMenuItems()
{
    QVector<MAction*> vector(1);
    //% "Example action"
    vector[0] = new MAction(qtTrId("dcp_skel_appl_action"), this);
    vector[0]->setLocation(MAction::ApplicationMenuLocation);
    return vector;
}

DcpBrief* SkeletonApplet::constructBrief(int)
{
    return new SkeletonBrief();
}

