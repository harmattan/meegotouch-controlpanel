#include <QtGui>
#include <QDebug>
#include <MAction>
#include <MTheme>
#include <DcpWidget>
#include "dcpskelbuttonapplet.h"
#include "dcpskelbutton.h"
#include "dcpskelbuttonbrief.h"

Q_EXPORT_PLUGIN2(skelbuttonapplet, SkelButtonApplet)

void SkelButtonApplet::init()
{
};

DcpWidget* SkelButtonApplet::constructWidget(int widgetId)
{
    // No views for button-like applets by default
    Q_UNUSED(widgetId);
    return 0;
}

QString SkelButtonApplet::title() const
{
    //% "SkelButton applet"
    return qtTrId("dcp_skel_appl_titl");
}

QVector<MAction*> SkelButtonApplet::viewMenuItems()
{
    QVector<MAction*> vector(1);
    //% "Example action"
    vector[0] = new MAction(qtTrId("dcp_skel_appl_action"), this);
    vector[0]->setLocation(MAction::ApplicationMenuLocation);
    return vector;
}

DcpBrief* SkelButtonApplet::constructBrief(int)
{
    return new SkelButtonBrief();
}

