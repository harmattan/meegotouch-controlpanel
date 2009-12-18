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

#define DEBUG
#include "dcpdebug.h"

DcpBriefWidget::DcpBriefWidget (
        DcpAppletMetadata *metadata, 
        DuiWidget         *parent)
: DuiWidget (parent), 
    m_RealWidget (0), 
    m_Metadata (0), 
    m_Hidden (true)
{
    QGraphicsLinearLayout* layout;
    
    layout = new QGraphicsLinearLayout (this);
    layout->setContentsMargins (0,0,0,0);

    setMetadata (metadata);
}

DcpBriefWidget::DcpBriefWidget (
        int               widgetTypeId,
        const QString    &line1,
        const QString    &line2,
        DuiWidget        *parent)
: DuiWidget (parent),
    m_Metadata (0),
    m_Hidden (true)
{
    QGraphicsLinearLayout* wlayout = new QGraphicsLinearLayout (this);
    wlayout->setContentsMargins (0, 0, 0, 0);

    DCP_WARNING ("Unsupported widget type: %d", widgetTypeId);
   

    DcpButton * toggle = new DcpButton (this);

    //toggle->setIconId ("");
    //connect (toggle, SIGNAL (smallToggled (bool)),
    //        metadata, SLOT (setToggle (bool)));
    
    m_RealWidget = toggle;
    m_RealWidget->setText1 (line1);
    m_RealWidget->setText2 (line2);
    ((QGraphicsLinearLayout*) layout())->addItem (m_RealWidget);
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
            DCP_DEBUG ("calling constructToggle()");
            m_RealWidget = constructToggle (m_Metadata);
            break;

        case DCPLABEL2IMAGE :
            DCP_DEBUG ("calling constructImage()");
            m_RealWidget = constructImage ();
            break;

        default:
            DCP_DEBUG ("calling DcpButton()");
            m_RealWidget = new DcpButton (this);
            break;
    }


    if (m_RealWidget) {
        m_RealWidget->setText1 (m_Metadata->text1());
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
    }

    m_Metadata = metadata;

    /*
     * If we have a metadata object we can construct a widget for that and then
     * we can connect some signals.
     */
    if (m_Metadata) {
        // FIXME: This might cause a race condition? What if the matedata sends
        // a signal when we are not connected yet?
        constructRealWidget (m_Metadata->widgetTypeID());

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
        dcpMarkAsMaybeBad (m_Metadata);
        m_RealWidget->setText1 (m_Metadata->text1());
        if (isVisible()) {
            updateContents ();
        }
        dcpUnmarkAsMaybeBad (m_Metadata);
    }
}

DcpButtonImage * 
DcpBriefWidget::constructImage ()
{
    DcpButtonImage* image = new DcpButtonImage(this);
    return image;
}

DcpButtonToggle *
DcpBriefWidget::constructToggle (
        const DcpAppletMetadata *metadata)
{
    DcpButtonToggle *toggle = new DcpButtonToggle (this);

    if (metadata) {
        connect (toggle, SIGNAL (smallToggled (bool)),
                 metadata, SLOT (setToggle (bool)));
    }

    return toggle;
}

void
DcpBriefWidget::updateContents ()
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
            connect (m_Metadata, SIGNAL (briefChanged ()), 
                this, SLOT (updateContents()));

        updateContents();
    }
}

void 
DcpBriefWidget::hideEvent (
        QHideEvent     *event)
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

