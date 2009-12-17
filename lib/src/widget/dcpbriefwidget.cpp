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

/*
 * Constructs the content of the DcpBriefWidget according to the widget type.
 * This is a separate code so the inherited classes might use other code,
 * possibly without any information about the applet variant. This way we can
 * implement internal brief widgets also.
 */
void
DcpBriefWidget::constructRealWidget (
        int                widgetTypeId)
{
    switch (widgetTypeId) {
        case DCPLABELBUTTON:
        case DCPLABEL2BUTTON:
            m_RealWidget = constructToggle (m_Metadata);
            break;

        case DCPLABEL2IMAGE :
            m_RealWidget = constructImage (m_Metadata);
            break;

        default:
            m_RealWidget = new DcpButton (this);
            break;
    }


    if (m_RealWidget) {
        retranslateUi ();
        ((QGraphicsLinearLayout*) layout())->addItem (m_RealWidget);
    }

}

void 
DcpBriefWidget::setMetadata (
        DcpAppletMetadata *metadata)
{
    // can be optimized if necessery (not recreating the widget, just updating 
    // its contents)
    if (m_RealWidget) 
        m_RealWidget->deleteLater();

    /*
     * If we had an old metadata object. Not a fat chance for that...
     */
    if (m_Metadata) { 
        /* 
         * Metadata is owned by the appletdb, so not removed, only disconnected
         * both ways.
         */
        disconnect (m_Metadata, 0, this, 0);
        disconnect (this, 0, m_Metadata, 0);
        // FIXME: I think this would not be a good ide, we can not disconnect 
        // all functions, because for example we will loose hide/show signals.
        // And who knows what else are we going to connect in the future.
        // this->disconnect ();
    }

    m_Metadata = metadata;

    /*
     * If we have a metadata object we can construct a widget for that and then
     * we can connect some signals.
     */
    if (m_Metadata) {
        // FIXME: This might cause a race condition? What if the matedata sends
        // a signal when we are not connected yet?
        dcpMarkAsMaybeBad (metadata);
        constructRealWidget (m_Metadata->widgetTypeID());
        dcpUnmarkAsMaybeBad(metadata);

        connect (this, SIGNAL (clicked()), 
                m_Metadata, SLOT (slotClicked()));
        connect (this, SIGNAL (clicked()),
                m_Metadata, SIGNAL (activate ()));
        connect (m_Metadata, SIGNAL (briefChanged()), 
                this, SLOT (updateContents()));
    }
}

void 
DcpBriefWidget::retranslateUi ()
{
    if (m_Metadata) {
        dcpMarkAsMaybeBad(m_Metadata);
        m_RealWidget->setText1(m_Metadata->text1());
        updateContents();
        dcpUnmarkAsMaybeBad(m_Metadata);
    }
}

DcpButtonImage* DcpBriefWidget::constructImage(
        const DcpAppletMetadata* metadata)
{
    DcpButtonImage* image = new DcpButtonImage(this);

    if (metadata) {
        image->setImageName(metadata->image());
    }

    return image;
}

DcpButtonToggle *
DcpBriefWidget::constructToggle(
        const DcpAppletMetadata* metadata)
{
    DcpButtonToggle* toggle = new DcpButtonToggle (this);

    if (metadata) {
        toggle->setSmallToggle (metadata->toggle());
        toggle->setIconId (metadata->toggleIconId());
        connect (toggle, SIGNAL (smallToggled(bool)),
             metadata, SLOT (setToggle(bool)));
    }

    return toggle;
}

void DcpBriefWidget::updateContents ()
{
    if (m_Metadata) {
        dcpMarkAsMaybeBad (m_Metadata);
        // for all:
        m_RealWidget->setText2 (m_Metadata->text2());

        // toggle specific:
        DcpButtonToggle* toggle = qobject_cast<DcpButtonToggle*>(m_RealWidget);
        if (toggle) {
            toggle->setSmallToggle (m_Metadata->toggle());
            toggle->setIconId (m_Metadata->toggleIconId());
        }

        // image specific:
        DcpButtonImage* image = qobject_cast<DcpButtonImage*>(m_RealWidget);
        if (image) {
            image->setImageName (m_Metadata->image());
        }
        dcpUnmarkAsMaybeBad (m_Metadata);
    }
}

void 
DcpBriefWidget::showEvent (
        QShowEvent *event)
{
    Q_UNUSED (event);
    Q_ASSERT (m_RealWidget);

    if (m_Hidden) { 
        // prevents multiple showEvents coming
        m_Hidden = false;

        connect (m_RealWidget, SIGNAL(clicked()), 
                this, SIGNAL(clicked()));

        if (m_Metadata)
            connect (m_Metadata, SIGNAL (briefChanged()), 
                this, SLOT (updateContents()));

        updateContents();
    }
}

void DcpBriefWidget::hideEvent ( QHideEvent * event )
{
    Q_UNUSED (event);
    Q_ASSERT (m_RealWidget);

    if (!m_Hidden) {// prevents multiple hideEvents coming
        m_Hidden = true;

        disconnect (m_RealWidget, SIGNAL(clicked()), 
                this, SIGNAL(clicked()));

        if (m_Metadata)
            disconnect (m_Metadata, SIGNAL (briefChanged()), 
                this, SLOT (updateContents()));
    }
}

