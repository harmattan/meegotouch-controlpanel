/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpcategorycomponent.h"
#include "dcpappletbuttons.h"

#include <MContainer>
#include <QGraphicsLinearLayout>

#include "dcpdebug.h"

/*!
 * Constructor that uses DcpCategoryInfo to create a DcpCategoryComponent.
 */
DcpCategoryComponent::DcpCategoryComponent (
            DcpComponent            *category, 
            const DcpCategoryInfo  *categoryInfo,
            QGraphicsWidget        *parent)
: DcpComponent (category, categoryInfo->appletCategory, parent, 
                categoryInfo->titleId),
    m_AppletButtons(0),
    m_CategoryInfo (categoryInfo)
{
}


DcpCategoryComponent::~DcpCategoryComponent()
{
}


void
DcpCategoryComponent::setTitle (
        const QString &title)
{
    DcpComponent::setTitle (title);
}

void
DcpCategoryComponent::retranslateUi()
{
    if (m_CategoryInfo) {
        setTitle (qtTrId (m_CategoryInfo->titleId));
    } else {
        setTitle (qtTrId (DCP_STR(m_LogicalId)));
    }
}

void
DcpCategoryComponent::createContents ()
{
}

void 
DcpCategoryComponent::reload ()
{
}

// ! Can be misleading, because it returns the count of the items already loaded
int
DcpCategoryComponent::getItemCount ()
{
    return 0;
}

