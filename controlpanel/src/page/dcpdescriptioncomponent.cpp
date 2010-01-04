/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpdescriptioncomponent.h"

#include <DuiLabel>
#include <DuiContainer>

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLinearLayout>

/*!
 * \class DcpDescriptionComponent
 * \brief DcpDescriptionComponent is a DcpComponent which is meant for
 * the main screen to providethe button that describes an an applet category.
 *
 * It displays a title and description about the category, and requests
 * the page switching if the user clicked on it.
 * Currently uses DuiContainer for all rendering stuff. 
 */
DcpDescriptionComponent::DcpDescriptionComponent(
        DcpCategory *category,
        const QString& title,
        QGraphicsWidget *parent) 
: DcpComponent (category, title, parent),
    m_Container (0)
{
    createContents ();
}


void 
DcpDescriptionComponent::createContents ()
{
    m_Container = new DuiContainer (this);
    m_Container->setAcceptedMouseButtons(0);
    setTitle (title());

    m_Description = new DuiLabel (m_Container);
    m_Description->setObjectName ("ComponentDescription");

    // FIXME: TODO move this to css when it becomes possible to do so
    m_Description->setAcceptedMouseButtons (0);
    m_Description->setSizePolicy (
            QSizePolicy::Expanding, 
            QSizePolicy::Expanding);

    m_Container->setCentralWidget (m_Description);

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(this);
    layout->addItem (m_Container);
}

void
DcpDescriptionComponent::setTitle (
        const QString& title)
{
    Q_ASSERT (m_Container);
    m_Container->setTitle (title);
}

void
DcpDescriptionComponent::setDescription (
        const QString& desc)
{
    m_Description->setText (desc);
}

void 
DcpDescriptionComponent::setTextAlignment (
        Qt::Alignment align)
{
    m_Description->setAlignment (align);
}

