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

#include "panningdetector.h"

#include "../../../lib/src/dcpdebug.h"

static const int LOAD_AT_ONCE_MAX = 1;
static const int TIMER_STOPPED = -1;

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
    m_LoadTimer(TIMER_STOPPED),
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
    m_LoadTimer(TIMER_STOPPED),
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
#ifndef DISABLE_DELAYED_LOADING
        if (!m_PanningDetector) {
            m_PanningDetector = new PanningDetector(this);
            connect (m_PanningDetector, SIGNAL(panningStopped()),
                     this, SLOT(continueLoading()));
        }
        continueLoading();
#else
        // FIXME this is a hack to disable the applet delayed loading until
        // we can solve the !updateAll assert, which seems a Qt bug
        while (loadNextItem()) ;
#endif
    } else {
        stopLoading();
    }
}

void
DcpAppletButtons::stopLoading()
{
    pauseLoading();
    if (m_PanningDetector) {
       // this is to avoid overhead of the signals
       m_PanningDetector->deleteLater();
       m_PanningDetector = 0;
    }
    if (m_LoadingMetadatas) {
        delete m_LoadingMetadatas;
        m_LoadingMetadatas = 0;
        m_LoadPosition = 0;
        emit loadingFinished();
    }
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
DcpAppletButtons::pauseLoading()
{
    if (m_LoadTimer != TIMER_STOPPED) {
        killTimer(m_LoadTimer);
        m_LoadTimer = TIMER_STOPPED;
    }
}

void
DcpAppletButtons::continueLoading ()
{
    if (m_LoadTimer == TIMER_STOPPED) {
        m_LoadTimer = startTimer(0);
    }
}

bool
DcpAppletButtons::loadNextItem ()
{
    Q_ASSERT(m_LoadingMetadatas);
    // load at maximum LOAD_AT_ONCE elements:
    int metadataCount = m_LoadingMetadatas->count();

    int maxPos = qMin(metadataCount, m_LoadPosition + LOAD_AT_ONCE_MAX);

    for (; m_LoadPosition < maxPos; m_LoadPosition++) {
        DcpAppletMetadata*& item = (*m_LoadingMetadatas)[m_LoadPosition];
        Q_ASSERT(item);
        addComponent (item);
        item = 0;
    }
    if (m_LoadPosition >= metadataCount) {
        stopLoading();
        return false;
    }
    return true;
}

void
DcpAppletButtons::timerEvent (QTimerEvent* event)
{
    if (m_LoadTimer == event->timerId()) {
        // "pause" the loading process if user is panning
        Q_ASSERT(m_PanningDetector);
        if (m_PanningDetector->isPanning()) {
            DCP_DEBUG("Loading PAUSED until user stops panning");
            pauseLoading();
            return;
        }

        loadNextItem();
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




