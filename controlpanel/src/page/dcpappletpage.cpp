/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpappletpage.h"
#include "dcpwrongapplets.h"

#include <DcpWidget>
#include <DcpAppletIf>
#include <DcpAppletMetadata>

#include <DuiLabel>
#include <DuiLocale>
#include <DuiApplication>
#include <DuiAction>
#include <QtDebug>

#define DEBUG
#include "dcpdebug.h"

DcpAppletPage::DcpAppletPage (
        DcpAppletMetadata *metadata):
    DcpPage (),
    m_Metadata (metadata),
    m_ReloadNeeded (false),
    m_MainWidget (0),
    m_MissingLabel (0)
{
    DCP_DEBUG ("");
    QObject::connect(qApp, SIGNAL(localeSettingsChanged()),
                     this, SLOT(loadAppletTranslations()));
}


DcpAppletPage::~DcpAppletPage ()
{
    DCP_DEBUG ("");
    dropWidget ();
}

/*!
 * Will refresh the content of the applet page calling the appropriate function.
 * If the content is not yet created will call the createContent () function, if
 * the content is created but the metadata is changed (so reload is needed) will
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
    loadAppletTranslations ();
    loadMainWidget ();
}

bool 
DcpAppletPage::hasWidget ()
{
    DCP_DEBUG ("Returning %s", m_MainWidget ? "true" : "false");
    return m_MainWidget;
}

bool 
DcpAppletPage::hasError ()
{
    DCP_DEBUG ("Returning %s", m_MissingLabel ? "true" : "false");

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

    if (m_Metadata && m_Metadata->isValid()) {
        if (m_Metadata->applet()) {
            /*
             * If the plugin is available (loaded) we call it to create a new
             * view. (Here we got the widgetId from the plugin itself using the
             * DCP/Part key of the desktop file.)
             */
            changeWidget (m_Metadata->getMainWidgetId ());

            return;
        } else if (m_Metadata->hasApplicationCommand ()) {
            /*
             * If the applet is not loaded from a binary file, but it has an
             * activation command line we execute an external application.
             *
             * FIXME: This should not block...
             */
            const char *command;

            command = m_Metadata->applicationCommand().toLatin1().constData();
            DCP_DEBUG ("Executing command '%s'", command);
            system (command);

            return;
        }

        DCP_WARNING ("The metadata has no loaded plugin nor an external "
                "command defined");
    } else {
        DCP_WARNING ("The metadata is not valid.");
    }

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
    loadAppletTranslations();
    loadMainWidget ();
    DcpPage::reload ();
}

void 
DcpAppletPage::back ()
{
    DCP_DEBUG ("");
    if (handle().isStandalone  && m_MainWidget->referer() == -1)
    {
       DCP_DEBUG("This is a standalone applet"); 
       qApp->exit(0);
       return;
    }
    if (!m_MainWidget || m_MainWidget->back())
        DcpPage::back();
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
    newMainWidget = m_Metadata->applet()->constructWidget (widgetId);
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
                DCP_STR (m_Metadata->name()),
                widgetId,
                newMainWidget->getWidgetId ());
    }

    if (!m_MainWidget) {
        return;
    }

    if (this_is_a_new_widget) {
        setPannableAreaInteractive (m_MainWidget->pagePans());

        connect (m_MainWidget, SIGNAL (changeWidget(int)), 
                this, SLOT(changeWidget(int)));

        connect (m_MainWidget, SIGNAL (activatePluginByName (const QString &)),
                m_Metadata, SLOT (activatePluginByName (const QString &)));
    
    }

    clearActions();
    QVector<DuiAction*> vector = m_Metadata->applet()->viewMenuItems();
    if (!vector.isEmpty())
        for (int i = 0; i < vector.size(); i++)
            addAction(vector[i]);
    appendWidget (m_MainWidget);


    retranslateUi();
}

void 
DcpAppletPage::setMetadata (
        DcpAppletMetadata *metadata)
{
    DCP_DEBUG ("*** metadata = %p", metadata);

    if (m_Metadata == metadata) {
        DCP_WARNING ("The same metadata already set.");
        return;
    }

    m_Metadata = metadata;
    m_ReloadNeeded = true;
    setReferer (PageHandle::NOPAGE); 
}

void
DcpAppletPage::retranslateUi ()
{
    DCP_DEBUG ("");

    if (m_Metadata && m_Metadata->applet()) {
        setTitle(m_Metadata->applet()->title());
    }
}

void
DcpAppletPage::loadAppletTranslations ()
{
    if (!m_Metadata) return;
    QString catalog = m_Metadata->translationCatalog();
    if (catalog.isEmpty()) return;

    DuiLocale locale; // gets the current locale
    locale.installTrCatalog(catalog + ".qm"); // install engineering english
    locale.installTrCatalog(catalog); // install real translation, if any
    DuiLocale::setDefault(locale);
    DCP_DEBUG("Translation %s loaded.", qPrintable(catalog));
}

