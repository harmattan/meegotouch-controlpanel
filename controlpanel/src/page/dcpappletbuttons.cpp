/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpappletbuttons.h"

#include <Pages>
#include <DcpAppletDb>
#include <DcpBriefComponent>
#include <DcpAppletMetadata>
#include <DcpApplet>

#include <DuiSceneManager>
#include <DuiGridLayoutPolicy>
#include <DuiLinearLayoutPolicy>

#include "dcpdebug.h"

/*!
 * \class DcpAppletButtons
 * \brief A container which contains buttons that represents the applets.
 */
DcpAppletButtons::DcpAppletButtons (
        const QString      &logicalId,
        const QString      &categoryName,
        const QString      &title,
        QGraphicsWidget    *parent) 
: DcpMainCategory (title, parent, logicalId), 
    m_CategoryName (categoryName),
    m_LogicalId (logicalId),
    m_CategoryInfo (0)
{
    setCreateSeparators (true);
    setMaxColumns (2);
    createContents();
    setMattiID ("DcpAppletButtons::" + logicalId + "::" + categoryName);
}

DcpAppletButtons::DcpAppletButtons (
        const DcpCategoryInfo  *categoryInfo,
        const QString          &title,
        QGraphicsWidget        *parent)
: DcpMainCategory (title, parent, categoryInfo->titleId),
    m_CategoryName (categoryInfo->appletCategory),
    m_CategoryInfo (categoryInfo)
{
    setCreateSeparators (true);
    setMaxColumns (2);
    createContents ();
    setMattiID (
            QString ("DcpAppletButtons::") + 
            categoryInfo->titleId + "::" + 
            categoryInfo->appletCategory);
}


void 
DcpAppletButtons::createContents ()
{
    DCP_DEBUG ("");
    /*
     * Getting the list of applet variants (metadata objects) that will go into
     * this widget.
     */
    DcpAppletMetadataList metadatas;
    if (logicalId() == DcpMain::mostRecentUsedTitleId) {
        metadatas = DcpAppletDb::instance()->listMostUsed ();
    } else {
        bool        withUncategorized;
        const char *names[3];

        withUncategorized = m_CategoryInfo && 
            m_CategoryInfo->subPageId == PageHandle::Applications;

        if (m_CategoryInfo) {
            names[0] = m_CategoryInfo->titleId;
            names[1] = m_CategoryInfo->appletCategory;
        } else {
            names[0] = DCP_STR (m_LogicalId);
            names[1] = DCP_STR (m_CategoryName);
        }
        names[2] = 0;

        metadatas = DcpAppletDb::instance()->listByCategory (names, 2,
                    withUncategorized ? dcp_category_name_enlisted : NULL);
    }

    /*
     * If we have a category info that might contain static elements, like the
     * 'accounts & applications' contain the 'service accounts' and
     * 'applications' static elements.
     * FIXME consider removing it since we do not need it anymore
     */
    if (m_CategoryInfo && m_CategoryInfo->staticElements) {
        const DcpCategoryInfo *element;

        for (int cnt = 0; ; ++cnt) {
            element = &m_CategoryInfo->staticElements[cnt];
            if (element->titleId == 0)
                break;

  /*          addComponent (
                    element->appletCategory,
                    "",
                    element->subPageId);
*/
        }
    }

    // adds the briefwidgets
    foreach (DcpAppletMetadata* item, metadatas) {
        addComponent (item);
    }
}


void
DcpAppletButtons::addComponent (
        DcpAppletMetadata *metadata)
{
    DcpBriefComponent *component;
    component = new DcpBriefComponent (DcpAppletDb::instance()->applet(metadata->name()), this, logicalId());
    component->setSubPage (PageHandle::APPLET, metadata->name());

    appendWidget (component);
}


void 
DcpAppletButtons::reload ()
{
//    This is used only for reloading the sequence of the most used items
//
//    FIXME, maybe we could make it more optimal with reusing the existing
//    widgets (at most one additional widget is coming, at most one is to be
//    removed)
//

    deleteItems ();
    createContents ();
}


