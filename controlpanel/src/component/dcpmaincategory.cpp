/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpmaincategory.h"

#include <DuiLayout>
#include <DuiGridLayoutPolicy>
#include <DuiLinearLayoutPolicy>
#include <DuiSceneManager>

#include <QtDebug>
#include <DuiSeparator>

//#define DEBUG
#include "../../../lib/src/dcpdebug.h"

static const QString SEPARATOR_OBJECTNAME = "DcpSmallSeparator";

DcpMainCategory::DcpMainCategory (
        const QString &title, 
        QGraphicsWidget *parent,
        const QString& logicalId) 
: DcpCategory(title, parent, logicalId),
    m_ColCount (0),
    m_RowCount (0),
    m_ItemCount (0),
    m_CreateSeparators (false),
    m_HasLastSeparator (false)
{
    m_Layout = new DuiLayout(this);

    m_LandscapeLayout = new DuiGridLayoutPolicy (m_Layout);

    m_Layout->setPolicy (m_LandscapeLayout);
    m_PortraitLayout = new DuiLinearLayoutPolicy (m_Layout, Qt::Vertical);

    setLayout(m_Layout);
}

DcpMainCategory::~DcpMainCategory ()
{
}


void 
DcpMainCategory::deleteItems ()
{
    if (!m_Layout) return;
    m_ItemCount = m_RowCount = m_ColCount = 0;

    // delete all items in all policies:
    foreach (DuiAbstractLayoutPolicy* policy, m_Layout->registeredPolicies()){
        for (int i=policy->count()-1; i >= 0; i--){
            QGraphicsWidget* widget = (QGraphicsWidget*)
                                      (policy->itemAt(i)->graphicsItem());
            Q_ASSERT(widget);
            m_Layout->removeItem(widget);
            widget->deleteLater();
        }
    }
}

void 
DcpMainCategory::setHorizontalSpacing (
        int space)
{
    m_LandscapeLayout->setHorizontalSpacing(space);
}

void 
DcpMainCategory::setVerticalSpacing (
        int space)
{
    m_LandscapeLayout->setVerticalSpacing (space);
    m_PortraitLayout->setSpacing (space);
}


/*!
 * Appends a new item to the widget. Handles two column layout automatically.
 * There is no function to add a long line, but as I see we don't need that
 * feature right now. Anyway, it is easy to implement such a function.  
 */
void 
DcpMainCategory::appendWidget (
        DcpComponent *component)
{
    DCP_DEBUG ("APPENDING to %p", this);
    appendSeparatorsIfNeeded ();

    m_LandscapeLayout->addItemAtPosition (component, m_RowCount, m_ColCount);
    m_PortraitLayout->addItem (component);
    
    incrementRowAndCol ();
    ++m_ItemCount;

    DcpCategory::add (component);
}

void 
DcpMainCategory::createContents ()
{
}

/*
 * FIXME: This is clearly not necessary!
 */
void 
DcpMainCategory::onOrientationChange (
        const Dui::Orientation &orientation)
{
    if (orientation == Dui::Portrait) {
        m_Layout->setPolicy (m_PortraitLayout);
    } else {
        m_Layout->setPolicy (m_LandscapeLayout);
    }

    DcpCategory::onOrientationChange (orientation);
}

void 
DcpMainCategory::showEvent (
        QShowEvent *)
{
    if (sceneManager()) {
        onOrientationChange(sceneManager()->orientation());
    }
}

void 
DcpMainCategory::setCreateSeparators (
        bool create)
{
    m_CreateSeparators = create;
}

void
DcpMainCategory::incrementRowAndCol ()
{
    ++m_ColCount;
    if (m_ColCount >= m_MaxColumns) {
        m_ColCount = 0;
        m_RowCount++;
    }
}

void
DcpMainCategory::appendSeparatorsIfNeeded ()
{
    DuiSeparator  *separator;

    DCP_DEBUG ("");

    /*
     * We have this feature to disable separators. 
     * FIXME: It seems to be useless though.
     */ 
    if (!m_CreateSeparators)
        return;

    /*
     * If this is going to be the very first element or if it is not the first
     * element of a new row we don't need to add any separators.
     */
    if (m_ItemCount == 0 ||
        m_ColCount != 0)
        return;

    /*
     * Adding as much separators as needed to get to the next row.
     */
    do {
        separator = new DuiSeparator (this);
        separator->setObjectName (SEPARATOR_OBJECTNAME);
        /*
         * We will not add the separator to the m_PortraitLayout, we don't want
         * to see them in portrait mode.
         */
        m_LandscapeLayout->addItemAtPosition (
                separator, m_RowCount, m_ColCount);
        
        incrementRowAndCol ();
    } while (m_ColCount != 0);
}


void 
DcpMainCategory::setMaxColumns (
        int columns)
{
    m_MaxColumns = columns;
    for (int col = 0; col < m_MaxColumns; col++) {
        m_LandscapeLayout->setColumnStretchFactor (col, 1);
    }
}

int 
DcpMainCategory::maxColumns (void)
{
    return m_MaxColumns;
}

/*
 * FIXME: What?
 */
void 
DcpMainCategory::setDoNotRemoveLastSeparator (
        bool remove)
{
    m_HasLastSeparator = remove;
}


