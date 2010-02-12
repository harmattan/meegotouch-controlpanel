/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpappletbuttons.h"

#include <Pages>
#include <DcpAppletDb>
#include <DcpBriefComponent>
#include <DcpAppletMetadata>
#include <DcpApplet>

#include <QCoreApplication>
#include <QtDebug>
#include <QTimer>
#include <DuiSceneManager>
#include <DuiGridLayoutPolicy>
#include <DuiLinearLayoutPolicy>

#include "panningdetector.h"

#define DEBUG
#include "../../../lib/src/dcpdebug.h"

static const int LOAD_AT_ONCE_MAX = 2;

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
    m_CategoryInfo (0),
    m_LoadPosition (0),
    m_LoadingMetadatas (0),
    m_PanningDetector (0)
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
    m_CategoryInfo (categoryInfo),
    m_LoadPosition (0),
    m_LoadingMetadatas (0),
    m_PanningDetector (0)
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
    if (logicalId() == DcpMain::mostRecentUsedTitleId) {
        // additional copy (with implicit sharing) to be able to clear whole mem up
        m_LoadingMetadatas = new DcpAppletMetadataList(
                                    DcpAppletDb::instance()->listMostUsed ());
//        m_PortraitLayout->setObjectName ("MostUsedItems");
//        m_LandscapeLayout->setObjectName ("MostUsedItems");
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

        m_LoadingMetadatas = new DcpAppletMetadataList(
                DcpAppletDb::instance()->listByCategory (names, 2,
                withUncategorized ? dcp_category_name_enlisted : NULL));
    }

    /*
     * If we have a category info that might contain static elements, like the
     * 'accounts & applications' contain the 'service accounts' and
     * 'applications' static elements.
     */
    if (m_CategoryInfo && m_CategoryInfo->staticElements) {
        const DcpCategoryInfo *element;

        for (int cnt = 0; ; ++cnt) {
            element = &m_CategoryInfo->staticElements[cnt];
            if (element->titleId == 0)
                break;

            addComponent (
                    element->appletCategory,
                    "",
                    element->subPageId);
        }
    }
}

/*! \brief start the loading
 * It is called from outside so that the caller can connect on
 * loadingFinished signal before calling the method, if it wants
 * to get notified when loading finished.
 */
void
DcpAppletButtons::startLoading()
{
    /*
     * Adding the applet variants to the widget.
     */
    m_LoadPosition = 0;
    Q_ASSERT(m_LoadingMetadatas);
    if (m_LoadingMetadatas->count() > 0) {
        if (!m_PanningDetector) {
            m_PanningDetector = new PanningDetector(this);
        }
        QTimer::singleShot(0, this, SLOT(continueLoading()));
    } else {
        stopLoading();
    }
}

void
DcpAppletButtons::stopLoading()
{
    if (m_PanningDetector) {
       // this is to avoid overhead of the signals
       m_PanningDetector->deleteLater();
       m_PanningDetector = 0;
    }
    delete m_LoadingMetadatas;
    m_LoadingMetadatas = 0;
    m_LoadPosition = 0;
    emit loadingFinished();
}

/* \returns true if the container contains loaded or loading items */
bool
DcpAppletButtons::hasLoadingItems()
{
    if (m_LoadingMetadatas) {
        return m_LoadingMetadatas->count() > 0;
    } else {
        return getItemCount() > 0;
    }
}

void
DcpAppletButtons::continueLoading ()
{
    // "pause" the loading process until user is panning
    if (!m_PanningDetector) return;
    if (m_PanningDetector->isPanning()) {
        m_PanningDetector->notifyOnNextStop(this, SLOT(continueLoading()));
        return;
    }

    Q_ASSERT(m_LoadingMetadatas);
    int metadataCount = m_LoadingMetadatas->count();
    // load at maximum LOAD_AT_ONCE elements:
    int maxPos = qMin(metadataCount, m_LoadPosition + LOAD_AT_ONCE_MAX);

    for (; m_LoadPosition < maxPos; m_LoadPosition++) {
        DcpAppletMetadata*& item = (*m_LoadingMetadatas)[m_LoadPosition];
        addComponent (item);
        item = 0;
    }

    if (m_LoadPosition < metadataCount) {
        QTimer::singleShot(0, this, SLOT(continueLoading()));
    } else {
        stopLoading();
    }
}

void
DcpAppletButtons::addComponent (
        DcpAppletMetadata *metadata)
{
    DcpBriefComponent *component;
    component = new DcpBriefComponent (metadata, this, logicalId());
    component->setSubPage (PageHandle::APPLET, metadata->name());

    appendWidget (component);
}

void
DcpAppletButtons::addComponent (
        const QString       &briefTitleText,
        const QString       &briefSecondaryText,
        const PageHandle    &pageHandle)
{
    DcpBriefComponent *component;

    component = new DcpBriefComponent (
            briefTitleText,
            briefSecondaryText,
            this, logicalId());
    component->setSubPage (pageHandle);

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
    startLoading ();
}

QString 
DcpAppletButtons::mattiID ()
{
    return m_mattiID;
}

void 
DcpAppletButtons::setMattiID (
        const QString &mattiID)
{
    m_mattiID = mattiID;
}



