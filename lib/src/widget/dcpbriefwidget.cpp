/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpbriefwidget.h"
#include "dcpappletmetadata.h"
#include "dcpwidgettypes.h"
#include "dcpbutton.h"
#include "dcpbuttontoggle.h"
#include "dcpbuttonimage.h"
#include "dcpwrongapplets.h"

#include <DuiSceneManager>
#include <QGraphicsLinearLayout>
#include <QtDebug>

DcpBriefWidget::DcpBriefWidget (
        DcpAppletMetadata *metadata, 
        DuiWidget         *parent)
: DuiWidget (parent), 
    m_RealWidget (0), 
    m_Metadata (0), 
    m_Hidden (true)
{
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(this);
    layout->setContentsMargins(0,0,0,0);

    setMetadata (metadata);
}


DcpBriefWidget::~DcpBriefWidget()
{
}

void 
DcpBriefWidget::setMetadata (
        DcpAppletMetadata* metadata)
{
    // can be optimized if necessery (not recreating the widget, just updating 
    // its contents)
    if (m_RealWidget) 
        m_RealWidget->deleteLater();

    if (m_Metadata) { 
        // metadata is owned by the appletdb, so not removed, only disconnected
        disconnect (m_Metadata, 0, this, 0);
        this->disconnect();
    }
    Q_ASSERT (metadata);
    m_Metadata = metadata;

    dcpMarkAsMaybeBad (metadata);

    switch (m_Metadata->widgetTypeID()) {
        case DCPLABELBUTTON:
        case DCPLABEL2BUTTON:
            m_RealWidget = constructToggle (metadata);
            break;

        case DCPLABEL2IMAGE :
            m_RealWidget = constructImage (metadata);
            break;

        default:
            m_RealWidget = new DcpButton(this);
            break;
    }

    connect (this, SIGNAL (clicked()), 
            m_Metadata, SLOT (slotClicked()));
    connect (this, SIGNAL (clicked()),
        m_Metadata, SIGNAL (activate ()));


    if (m_RealWidget) {
        retranslateUi();
        ((QGraphicsLinearLayout*)layout())->addItem(m_RealWidget);
    }

    dcpUnmarkAsMaybeBad(metadata);
}

void DcpBriefWidget::retranslateUi()
{
    dcpMarkAsMaybeBad(m_Metadata);
    m_RealWidget->setText1(m_Metadata->text1());
    updateContents();
    dcpUnmarkAsMaybeBad(m_Metadata);
}

DcpButtonImage* DcpBriefWidget::constructImage(
        const DcpAppletMetadata* metadata)
{
    DcpButtonImage* image = new DcpButtonImage(this);
    image->setImageName(metadata->image());
    return image;
}

DcpButtonToggle* DcpBriefWidget::constructToggle(
        const DcpAppletMetadata* metadata)
{
    DcpButtonToggle* toggle = new DcpButtonToggle(this);
    toggle->setSmallToggle(metadata->toggle());
    toggle->setIconId(metadata->toggleIconId());
    connect (toggle, SIGNAL(smallToggled(bool)),
             metadata, SLOT(setToggle(bool)));
    return toggle;
}

void DcpBriefWidget::updateContents()
{
    dcpMarkAsMaybeBad(m_Metadata);
    // for all:
    m_RealWidget->setText2(m_Metadata->text2());

    // toggle specific:
    DcpButtonToggle* toggle = qobject_cast<DcpButtonToggle*>(m_RealWidget);
    if (toggle) {
        toggle->setSmallToggle(m_Metadata->toggle());
        toggle->setIconId(m_Metadata->toggleIconId());
    }

    // image specific:
    DcpButtonImage* image = qobject_cast<DcpButtonImage*>(m_RealWidget);
    if (image) {
        image->setImageName(m_Metadata->image());
    }
    dcpUnmarkAsMaybeBad(m_Metadata);
}

void DcpBriefWidget::showEvent ( QShowEvent * event )
{
    Q_UNUSED (event);
    Q_ASSERT(m_RealWidget && m_Metadata);

    if (m_Hidden) { // prevents multiple showEvents coming
        m_Hidden = false;

        connect (m_RealWidget, SIGNAL(clicked()), this, SIGNAL(clicked()));
        connect (m_Metadata, SIGNAL(briefChanged()), this, SLOT(updateContents()));

        updateContents();
    }
}

void DcpBriefWidget::hideEvent ( QHideEvent * event )
{
    Q_UNUSED (event);
    Q_ASSERT(m_RealWidget && m_Metadata);

    if (!m_Hidden) {// prevents multiple hideEvents coming
        m_Hidden = true;

        disconnect (m_RealWidget, SIGNAL(clicked()), this, SIGNAL(clicked()));
        disconnect (m_Metadata, SIGNAL(briefChanged()), this, SLOT(updateContents()));
    }
}

