/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpappletbuttons.h"

#include <Pages>
#include <DcpAppletDb>
#include <DcpBriefComponent>
#include <DcpAppletMetadata>
#include <DcpApplet>

#include <QtDebug>
#include <DuiSceneManager>
#include <DuiGridLayoutPolicy>
#include <DuiLinearLayoutPolicy>
#include "maintranslations.h"

#define DEBUG
#include "../../../lib/src/dcpdebug.h"

/*!
 * \class DcpAppletButtons
 * \brief A container which contains buttons that represents the
 * applets.
 */
DcpAppletButtons::DcpAppletButtons(
        const QString& logicalId,
        const QString& categoryName,
        const QString& title,
        QGraphicsWidget *parent) :
    DcpMainCategory (title, parent, logicalId), 
    m_CategoryName (categoryName)
{
    setCreateSeparators (true);
    setMaxColumns (2);
    createContents ();
    setMattiID ("DcpAppletButtons::" + logicalId + "::" + categoryName);
}

void 
DcpAppletButtons::createContents ()
{
    DcpAppletMetadataList list;
    int                   cnt = 0;

    DCP_WARNING ("*** logicalId = %s", DCP_STR (logicalId()));

    /*
     * Getting the list of applet variants (metadata objects) that will go into
     * this widget.
     */
    if (logicalId() == DcpMain::mostRecentUsedTitleId) {
        list = DcpAppletDb::instance()->listMostUsed();
    } else {
        list = DcpAppletDb::instance()->listByCategory (m_CategoryName);
    }

    if (logicalId() == QT_TRID_NOOP ("qtn_sett_main_combined")) {
        DCP_WARNING ("This is the applications category");
        addComponent (
                "Applications",
                "",
                PageHandle::ACCOUNTSANDAPPLICATIONS,
                false);
        ++cnt;
    }
    /*
     * Adding the applet variants to the widget.
     */
    foreach (DcpAppletMetadata *item, list) {
        cnt++;
        DCP_DEBUG ("   *** item->name = %s", DCP_STR (item->name()));
        //last item is impaired
        if (cnt == list.count() && cnt % 2 == 1) 
            addComponent (item, true);
        else
            addComponent (item, false);
    }

    m_PortraitLayout->setObjectName ("MostUsedItems");
    m_LandscapeLayout->setObjectName ("MostUsedItems");
    setVerticalSpacing (0);
}

void 
DcpAppletButtons::addComponent (
        DcpAppletMetadata *metadata, 
        bool               fullLine)
{
    DcpBriefComponent *component;
    
    component = new DcpBriefComponent (metadata, this, logicalId());
    component->setSubPage (PageHandle::APPLET, metadata->name());

    if (fullLine)
        add (component);
    else
        append (component);
}

void
DcpAppletButtons::addComponent (
        const QString       &briefTitleText,
        const QString       &briefSecondaryText,
        const PageHandle    &pageHandle,
        bool                 fullLine)
{
    DcpBriefComponent *component;
    
    component = new DcpBriefComponent (
            briefTitleText, 
            briefSecondaryText,
            this, logicalId());
    component->setSubPage (pageHandle);

    if (fullLine)
        add (component);
    else
        append (component);
}


void 
DcpAppletButtons::reload()
{
    deleteItems();
    createContents();
}

QString DcpAppletButtons::mattiID()
{
    return m_mattiID;
}

void DcpAppletButtons::setMattiID(const QString &mattiID)
{
    m_mattiID=mattiID;
}

