/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpappletpage.h"
#include "dcpwrongapplets.h"

#include <DcpWidget>
#include <DcpAppletIf>
#include <DcpAppletMetadata>
#include <DcpAppletLoader>

#include <DuiLabel>
#include <DuiLocale>
#include <DuiAction>
#include <QtDebug>

#define DEBUG
#include "dcpdebug.h"


DcpAppletPage::DcpAppletPage(DcpAppletMetadata *metadata):
    DcpPage(),
    m_Metadata(metadata),
    m_LoadedMetadata(0),
    m_MainWidget(0),
    m_MissingLabel(0)
{
    setHandle  (Pages::APPLET, metadata->name());
    setReferer (Pages::NOPAGE);
}

DcpAppletPage::~DcpAppletPage()
{
    if (m_LoadedMetadata) { dcpUnmarkAsMaybeBad(m_LoadedMetadata); }
    clearup();
    qDebug() << "appletpage destroy";
}

void DcpAppletPage::createContent()
{
    DcpPage::createContent();
    load();
}

bool DcpAppletPage::hasWidget() {
    return m_MainWidget;
}

bool DcpAppletPage::hasError() {
    return m_MissingLabel; 
}

void
DcpAppletPage::load()
{
    DCP_DEBUG ("------------------------------------------");
    DCP_DEBUG ("*** this             = %p", this);
    DCP_DEBUG ("*** m_Metadata       = %p", m_Metadata);
    DCP_DEBUG ("*** m_LoadedMetadata = %p", m_LoadedMetadata);

    if (m_LoadedMetadata) {
        dcpUnmarkAsMaybeBad (m_LoadedMetadata); 
    }

    if (m_Metadata) {
        dcpMarkAsMaybeBad (m_Metadata); 
    }

    m_LoadedMetadata = m_Metadata;

    
    if (m_Metadata && m_Metadata->isValid()) {
        if (m_Metadata->applet()) {
            /*
             * If the plugin is available (loaded) we call it to create a new
             * view.
             */
            if (m_Metadata->partID() != -1)
                changeWidget (m_Metadata->partID());
            else
                changeWidget (0);

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
    }

    Q_ASSERT (!m_MissingLabel);
    //% "Plugin not available"
    m_MissingLabel = new DuiLabel(qtTrId("dcp_no_applet_name"));
    m_MissingLabel->setAlignment(Qt::AlignCenter);
    append(m_MissingLabel);
    //% "Missing plugin"
    setTitle(qtTrId("dcp_no_applet_title"));
}

void DcpAppletPage::clearup()
{
    if (m_MainWidget) {
        m_MainWidget->deleteLater();
        m_MainWidget = 0;
    }
    if (m_MissingLabel) {
        m_MissingLabel->deleteLater();
        m_MissingLabel = 0;
    }
}

void DcpAppletPage::reload()
{
    if (m_Metadata != m_LoadedMetadata || !hasWidget()) {
        clearup();
        load();
    }
    DcpPage::reload();
    // means: referer should be set by pagefactory to the last page
    setReferer(Pages::NOPAGE); 
}

void DcpAppletPage::back()
{
    DCP_DEBUG ("*** m_MainWidget = %p", m_MainWidget);

    if (!m_MainWidget || m_MainWidget->back())
        DcpPage::back();
}

void DcpAppletPage::changeWidget(int widgetId)
{
    if (m_MainWidget != 0) {
        remove (m_MainWidget);
    }

    m_MainWidget = m_Metadata->applet()->constructWidget (widgetId);

    // checks if applet does provide the widget

    if (!m_MainWidget) {
        return;
    }
    setPannableAreaInteractive(m_MainWidget->pagePans());

    /*
     * FIXME: Are we sure this is a new widget that we never saw before and
     * never connected to its signals?
     */
    connect (m_MainWidget, SIGNAL (changeWidget(int)), 
            this, SLOT(changeWidget(int)));

    connect (m_MainWidget, SIGNAL (activatePluginByName (const QString &)),
            m_Metadata, SLOT (activatePluginByName (const QString &)));

    append(m_MainWidget);

    QVector<DuiAction*> vector = m_LoadedMetadata->applet()->viewMenuItems();
    if (!vector.isEmpty())
        for (int i = 0; i < vector.size(); i++)
            addAction(vector[i]);

    retranslateUi();
}

void DcpAppletPage::setMetadata (DcpAppletMetadata *metadata)
{
    DCP_DEBUG ("************************************");
    DCP_DEBUG ("*** setting %p", metadata);
    m_Metadata = metadata;
}

void DcpAppletPage::retranslateUi()
{
    if (m_LoadedMetadata && m_LoadedMetadata->applet()) {
        setTitle(m_LoadedMetadata->applet()->title());
    }
}

