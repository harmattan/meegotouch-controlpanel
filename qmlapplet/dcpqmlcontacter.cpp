#include "dcpqmlcontacter.h"
#include "dcpqmlapplet.h"
#include "dcpqmlwidget.h"

#include "duicontrolpanelif.h"
#include "dcpdebug.h"

DcpQmlContacter::DcpQmlContacter():
    QObject ()
{
}

DcpQmlContacter::~DcpQmlContacter()
{
}

/*
 * Returns true if the page the applet is on is standalone.
 *
 * A page is standalone if there is no other page before it in the page
 * stack. In this case the page has to show different back button image
 * (the icon of control panel).
 */
bool DcpQmlContacter::isStandalone() const
{
    DcpQmlApplet* applet = DcpQmlApplet::instance();
    dcp_failfunc_unless (applet, false);
    DcpQmlWidget* widget = applet->currentWidget();
    dcp_failfunc_unless (widget, false);

    QObject* page = (QObject*)widget->page();
    dcp_failfunc_unless (page, false);

    return page->property("isStandalone").toBool();
}

void DcpQmlContacter::popupMainPageAlone()
{
    DuiControlPanelIf iface;
    if (iface.isValid()) {
        iface.mainPage();
    }
}

