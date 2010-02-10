/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpmaincategory.h"

#include <DuiLayout>
#include <DuiGridLayoutPolicy>
#include <DuiLinearLayoutPolicy>
#include <DuiSceneManager>

#include <QtDebug>
#include <DuiSeparator>

#define DEBUG
#include "../../../lib/src/dcpdebug.h"

static const QString SeparatorObjectName = "DcpSmallSeparator";

DcpMainCategory::DcpMainCategory (
        const QString &title, 
        QGraphicsWidget *parent,
        const QString& logicalId) 
: DcpComponent (0, title, parent, logicalId),
    m_ColCount (0),
    m_RowCount (0),
    m_ItemCount (0),
    m_CreateSeparators (false)
{
    m_Layout = new DuiLayout (this);
    m_Layout->setAnimation(0);

    m_LandscapeLayout = new DuiGridLayoutPolicy (m_Layout);
    m_PortraitLayout = new DuiLinearLayoutPolicy (m_Layout, Qt::Vertical);
    
    m_Layout->setLandscapePolicy (m_LandscapeLayout);
    m_Layout->setPortraitPolicy (m_PortraitLayout);

    setLayout (m_Layout);
}


void 
DcpMainCategory::deleteItems ()
{
    if (!m_Layout) return;
    m_ItemCount = m_RowCount = m_ColCount = 0;

    // delete all items in all policies:
    foreach (DuiAbstractLayoutPolicy* policy, m_Layout->registeredPolicies()){
        for (int i = policy->count() - 1; i >= 0; i--){
            QGraphicsWidget* widget = (QGraphicsWidget*)
                                      (policy->itemAt(i)->graphicsItem());
            Q_ASSERT (widget);
            m_Layout->removeItem (widget);
            widget->deleteLater ();
        }
    }
}

void 
DcpMainCategory::setHorizontalSpacing (
        int space)
{
    m_LandscapeLayout->setHorizontalSpacing (space);
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

    m_LandscapeLayout->addItem (component, m_RowCount, m_ColCount);
    m_PortraitLayout->addItem (component);
    
    incrementRowAndCol ();
    ++m_ItemCount;
}

void 
DcpMainCategory::createContents ()
{
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
        separator->setObjectName (SeparatorObjectName);
        /*
         * We will not add the separator to the m_PortraitLayout, we don't want
         * to see them in portrait mode.
         */
        m_LandscapeLayout->addItem (
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
DcpMainCategory::maxColumns ()
{
    return m_MaxColumns;
}


