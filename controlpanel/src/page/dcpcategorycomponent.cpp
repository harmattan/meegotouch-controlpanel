/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpcategorycomponent.h"
#include "dcpappletbuttons.h"

#include <DuiContainer>
#include <QGraphicsLinearLayout>
#include <DuiSceneManager>

#define DEBUG
#include "../../../lib/src/dcpdebug.h"

/*!
 * Constructor that uses category name to create the component. Should use 
 * DcpCategoryInfo so this may be deprecated.
 */
DcpCategoryComponent::DcpCategoryComponent (
        DcpCategory       *category,
        const QString     &categoryName,
        const QString     &logicalId,
        QGraphicsWidget   *parent)
: DcpComponent (category, categoryName, parent, logicalId),
    m_CategoryName (categoryName),
    m_CategoryInfo (0),
    m_LogicalId (logicalId)
{
    createContents ();
    setMattiID ("DcpCategoryComponent::" + logicalId);
}

/*!
 * Constructor that uses DcpCategoryInfo to create a DcpCategoryComponent.
 */
DcpCategoryComponent::DcpCategoryComponent (
            DcpCategory            *category, 
            const DcpCategoryInfo  *categoryInfo,
            QGraphicsWidget        *parent)
: DcpComponent (category, categoryInfo->appletCategory, parent, 
                categoryInfo->titleId),
    m_CategoryName (categoryInfo->appletCategory),
    m_CategoryInfo (categoryInfo)
{
    createContents ();
    setMattiID (QString("DcpCategoryComponent::") + categoryInfo->titleId);
}


DcpCategoryComponent::~DcpCategoryComponent()
{
}


void 
DcpCategoryComponent::setTitle (
        const QString &title)
{
    m_Container->setTitle (title);
    DcpComponent::setTitle (title);
}

void
DcpCategoryComponent::retranslateUi ()
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
    QGraphicsLinearLayout *layout;

    m_Container = new DuiContainer (this);
    m_Container->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    if (m_CategoryInfo) 
        m_AppletButtons = new DcpAppletButtons (m_CategoryInfo, title());
    else
        m_AppletButtons = new DcpAppletButtons (
                logicalId(), m_CategoryName, title());

    m_Container->setCentralWidget (m_AppletButtons);
    layout = new QGraphicsLinearLayout (Qt::Vertical, this);
    layout->addItem (m_Container);
}

void 
DcpCategoryComponent::reload ()
{
    m_AppletButtons->reload();
}

int
DcpCategoryComponent::getItemCount ()
{
    return m_AppletButtons->getItemCount ();
}

void 
DcpCategoryComponent::onOrientationChange (
        const Dui::Orientation &orientation)
{
    m_AppletButtons->onOrientationChange(orientation);
}

QString 
DcpCategoryComponent::mattiID ()
{
    return m_mattiID;
}

void 
DcpCategoryComponent::setMattiID (
        const QString &mattiID)
{
    m_mattiID = mattiID;
}

