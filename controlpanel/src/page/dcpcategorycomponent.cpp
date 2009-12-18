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
 * \class DcpCategoryComponent
 * \brief A component for the recently used applets
 *
 * It is supplies the background and title for around DcpAppletButtons,
 * which contains the buttons. (Actually uses DuiContainer for that.)
 */

DcpCategoryComponent::DcpCategoryComponent(
                            DcpCategory *category,
                            const QString& categoryName,
                            const QString& logicalId,
                            QGraphicsWidget *parent)
         : DcpComponent(category, categoryName, parent, logicalId),
         m_CategoryName(categoryName)
{
    createContents();
    setMattiID ("DcpCategoryComponent::"+logicalId);
}

DcpCategoryComponent::~DcpCategoryComponent()
{
}

void DcpCategoryComponent::setTitle(const QString& title)
{
    m_Container->setTitle(title);
    DcpComponent::setTitle(title);
}

void DcpCategoryComponent::createContents()
{
    m_Container = new DuiContainer(this);
    m_Container->setSizePolicy(QSizePolicy::Expanding,
                                 QSizePolicy::Expanding);

    m_AppletButtons = new DcpAppletButtons(logicalId(), m_CategoryName, title());

    m_Container->setCentralWidget(m_AppletButtons);

    QGraphicsLinearLayout* layout =
        new QGraphicsLinearLayout(Qt::Vertical,this);
    layout->addItem(m_Container);
}

void DcpCategoryComponent::reload()
{
    m_AppletButtons->reload();
}

void DcpCategoryComponent::onOrientationChange
                            (const Dui::Orientation &orientation)
{
    m_AppletButtons->onOrientationChange(orientation);
}

QString DcpCategoryComponent::mattiID()
{
    return m_mattiID;
}

void DcpCategoryComponent::setMattiID(const QString &mattiID)
{
    m_mattiID = mattiID;
}
