/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpappletpage.h"

#include <DcpWidget>
#include <DcpAppletIf>
#include <DcpAppletMetadata>
#include <DcpAppletObject>

#include <DuiLabel>
#include <DuiLocale>
#include <DuiApplication>
#include <DuiAction>

#define DEBUG
#include "dcpdebug.h"

#include "duiwidgetcreator.h"
DUI_REGISTER_WIDGET_NO_CREATE(DcpAppletPage)

DcpAppletPage::DcpAppletPage (DcpAppletObject *applet, int widgetId):
    DcpPage (),
    m_Applet(applet),
    m_WidgetId(widgetId),
    m_ReloadNeeded (false),
    m_MainWidget (0),
    m_MissingLabel (0)
{
}


DcpAppletPage::~DcpAppletPage ()
{
    dropWidget ();
}

/*!
 * Will refresh the content of the applet page calling the appropriate function.
 * If the content is not yet created will call the createContent () function, if
 * the content is created but the applet is changed (so reload is needed) will
 * call the reload() function, otherwise will call the load() function that is
 * will activate the applet.
 */
void 
DcpAppletPage::refreshContent ()
{
    if (!isContentCreated()) {
        createContent ();
    } else if (m_ReloadNeeded) {
        reload ();
    } else {
        loadMainWidget ();
    }
}

void
DcpAppletPage::createContent ()
{
    DcpPage::createContent ();
    loadMainWidget ();
}

bool 
DcpAppletPage::hasWidget ()
{
    return m_MainWidget;
}

bool 
DcpAppletPage::hasError ()
{
    return m_MissingLabel;
}

/*!
 * This function might do three things. If the applet variant has a binary
 * applet it will call the binary and load the main widget of the applet
 * variant. If the applet variant has an application command (a shell command
 * that should be called when the applet is activated) the function will execute
 * the shell command. Finaly if neither the applet binary is loaded nor the
 * shell command is available this function will create wome widgets to show
 * that the applet is not available.
 */
void
DcpAppletPage::loadMainWidget ()
{
    DCP_DEBUG ("");

    if (m_Applet) {
       if (m_Applet->isAppletLoaded()) {
            /*
             * If the plugin is available (loaded) we call it to create a new
             * view. (Here we got the widgetId from the plugin itself using the
             * DCP/Part key of the desktop file.)
             */
            if (m_WidgetId < 0) {
                m_WidgetId = m_Applet->getMainWidgetId();
            }
            changeWidget (m_WidgetId);

            return;
        } else if (m_Applet->metadata()->hasApplicationCommand ()) {
            /*
             * If the applet is not loaded from a binary file, but it has an
             * activation command line we execute an external application.
             *
             * FIXME: This should not block...
             */
            const char *command;

            command = m_Applet->metadata()->applicationCommand().toLatin1().constData();
            DCP_DEBUG ("Executing command '%s'", command);
            system (command);

            return;
        }

        DCP_WARNING ("The applet has no loaded plugin nor an external "
                "command defined");
    } else {
        DCP_WARNING ("The applet is not valid.");
    }

    /*
     * Showing the 'plugin not available' label. We currently show this only if
     * the plugin is really not available, we will not show this if the plugin
     * is crashed. The plugin will be re-enabled (and most likely crash again)
     * when the user activates the applet by clicking on the brief.
     */
    if (!m_MissingLabel) {
        //% "Plugin not available"
        m_MissingLabel = new DuiLabel (qtTrId("dcp_no_applet_name"));
        m_MissingLabel->setAlignment (Qt::AlignCenter);
        appendWidget (m_MissingLabel);
        //% "Missing plugin"
        setTitle (qtTrId("dcp_no_applet_title"));
    }
}

void 
DcpAppletPage::dropWidget ()
{
    DCP_DEBUG ("");

    if (m_MainWidget) {
        removeWidget (m_MainWidget);
        m_MainWidget = 0;
    }

    dropMissingLabel ();
}

void 
DcpAppletPage::dropMissingLabel ()
{
    if (m_MissingLabel) {
        m_MissingLabel->deleteLater();
        m_MissingLabel = 0;
    }
}

void 
DcpAppletPage::reload ()
{
    DCP_DEBUG ("");

    if (hasWidget()) {
        dropWidget ();
    }
    loadMainWidget ();
    DcpPage::reload ();
}

void 
DcpAppletPage::back ()
{
    DCP_DEBUG ("");
    if (handle().isStandalone)
    {
       DCP_DEBUG("This is a standalone applet"); 
       qApp->exit(0);
       return;
    }
<<<<<<< HEAD:controlpanel/src/page/dcpappletpage.cpp
    if (!m_MainWidget || m_MainWidget->back())
        dismiss();//DcpPage::back();
=======
    DcpPage::back();
>>>>>>> 463626db3719896e1d1f90252be4dfe6f9ec3af6:controlpanel/src/page/dcpappletpage.cpp
}

void 
DcpAppletPage::changeWidget (
        int widgetId)
{
    DcpWidget  *newMainWidget;
    bool        this_is_a_new_widget;

    dropMissingLabel ();

    /*
     * Creating the widget and setting its widgetId.
     */
    newMainWidget = m_Applet->applet()->constructWidget (widgetId);
    this_is_a_new_widget = m_MainWidget != newMainWidget;

    if (m_MainWidget != 0 && this_is_a_new_widget) {
        /*
         * If this is not the same widget that we already have, we remove the
         * old one. It is possible the user started up the same applet just
         * backed from and then we might get the same widget!
         */
        dropWidget ();
    }
    /*
     * From now on, this is the widget we have. And if it is NULL, we just
     * return.
     */
    m_MainWidget = newMainWidget;

    if (this_is_a_new_widget &&
            newMainWidget != 0 && 
            !newMainWidget->setWidgetId (widgetId) &&
            newMainWidget->getWidgetId () != widgetId) {
            /*
             * We needed to set the widgetId, for it is a new widget, but we
             * could not set it.
             */
            DCP_WARNING ("The widgetId could not be set for applet '%s' "
                "widget %d it remains %d.",
                DCP_STR (m_Applet->metadata()->name()),
                widgetId,
                newMainWidget->getWidgetId ());
    }

    if (!m_MainWidget) {
        return;
    }

    if (this_is_a_new_widget) {
        setPannableAreaInteractive (m_MainWidget->pagePans());

        connect (m_MainWidget, SIGNAL (changeWidget(int)),
                 m_Applet, SLOT(activateSlot(int)));

        connect (m_MainWidget, SIGNAL (activatePluginByName (const QString &)),
                m_Applet, SLOT (activatePluginByName (const QString &)));
    }

    replaceActions(m_Applet->applet()->viewMenuItems());
    appendWidget (m_MainWidget);

    retranslateUi();
}

void
DcpAppletPage::replaceActions(const QVector<DuiAction*>& actions)
{
    foreach (DuiAction* action, m_Actions) {
        action->deleteLater();
    }
    m_Actions = actions;
    foreach (DuiAction* action, m_Actions) {
        addAction(action);
    }
}

void
DcpAppletPage::setApplet (
        DcpAppletObject *applet, int widgetId)
{
    DCP_DEBUG ("*** applet = %p", applet);

    if (m_Applet == applet && widgetId == m_WidgetId) {
        DCP_WARNING ("The same applet already set.");
        return;
    }

    m_Applet = applet;
    m_WidgetId = widgetId;
    m_ReloadNeeded = true;
    setReferer (PageHandle::NOPAGE); 
}

void
DcpAppletPage::retranslateUi ()
{
    DCP_DEBUG ("");

    if (m_Applet && m_Applet->applet()) {
        setTitle(m_Applet->applet()->title());
    }
}


