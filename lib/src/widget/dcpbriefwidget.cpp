/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpbriefwidget.h"
#include "dcpappletobject.h"
#include "dcpappletmetadata.h"
#include "dcpwidgettypes.h"
#include "dcpbutton.h"
#include "dcpbuttontoggle.h"
#include "dcpbuttonimage.h"
#include "dcpwrongapplets.h"

#include <DuiSceneManager>
#include <QGraphicsLinearLayout>
#include <QtDebug>

//#define DEBUG
#include "dcpdebug.h"

/******************************************************************************
 * Private data class for the DcpWidget class.
 */
class DcpBriefWidgetPrivate {
public:
    DcpBriefWidgetPrivate ();

    DcpButton *m_RealWidget;
    DcpAppletObject *m_Applet;
    bool m_Hidden;
};

DcpBriefWidgetPrivate::DcpBriefWidgetPrivate ():
    m_RealWidget (0), 
    m_Applet (0), 
    m_Hidden (true)
{
}


/******************************************************************************
 * Stuff for the DcpBriefWidget class.
 */
DcpBriefWidget::DcpBriefWidget (
        DcpAppletObject *applet, 
        DuiWidget         *parent):
    DuiWidget (parent), 
    d_ptr (new DcpBriefWidgetPrivate)
{
    QGraphicsLinearLayout* layout;
    
    layout = new QGraphicsLinearLayout (this);
    layout->setContentsMargins (0, 0, 0, 0);

    setApplet (applet);
}

DcpBriefWidget::DcpBriefWidget (
        int               widgetTypeId,
        const QString    &line1,
        const QString    &line2,
        DuiWidget        *parent):
    DuiWidget (parent),
    d_ptr (new DcpBriefWidgetPrivate)
{
    DcpButton    *toggle;
    QGraphicsLinearLayout* wlayout = new QGraphicsLinearLayout (this);
    wlayout->setContentsMargins (0, 0, 0, 0);

    /*
     * FIXME: I mean unused argument.
     * All this contructor seems strange, dcpbriefwidget would be about
     * interaction between the applet and the DcpButtons, consider
     * using DcpButton directly instead of this
     *
     */
    //DCP_WARNING ("Unsupported widget type: %d", widgetTypeId);
    Q_UNUSED(widgetTypeId);

    toggle = new DcpButton (this);
    d_ptr->m_RealWidget = toggle;
    d_ptr->m_RealWidget->setText1 (line1);
    d_ptr->m_RealWidget->setText2 (line2);
    ((QGraphicsLinearLayout*) layout())->addItem (d_ptr->m_RealWidget);
}


DcpBriefWidget::~DcpBriefWidget ()
{
    delete d_ptr;
}


/*
 * Constructs the content of the DcpBriefWidget according to the widget type.
 * This is a separate code so the inherited classes might use other code,
 * possibly without any information about the applet variant. This way we can
 * implement internal brief widgets also.
 */
void
DcpBriefWidget::constructRealWidget (int widgetTypeId)
{
    switch (widgetTypeId) {
        case DcpWidgetType::Toggle:
            DCP_DEBUG ("### DcpWidgetType::Toggle ###");
            d_ptr->m_RealWidget = constructToggle (d_ptr->m_Applet);
            break;

        case DcpWidgetType::Image:
            DCP_DEBUG ("### DcpWidgetType::Image ###");
            d_ptr->m_RealWidget = constructImage (d_ptr->m_Applet);
            break;

        default:
            DCP_DEBUG ("### DcpWidgetType::Label ###");
            d_ptr->m_RealWidget = new DcpButton (this);
            break;
    }


    if (d_ptr->m_RealWidget) {
        retranslateUi ();
        ((QGraphicsLinearLayout*) layout())->addItem (d_ptr->m_RealWidget);
    }
}

DcpAppletObject *
DcpBriefWidget::applet() const
{
    return d_ptr->m_Applet;
}

void 
DcpBriefWidget::setApplet (
        DcpAppletObject *applet)
{
    // can be optimized if necessery (not recreating the widget, just updating 
    // its contents)
    if (d_ptr->m_RealWidget) 
        d_ptr->m_RealWidget->deleteLater();

    /*
     * If we had an old applet object. Not a fat chance for that...
     */
    if (d_ptr->m_Applet) { 
        /* 
         * Metadata is owned by the appletdb, so not removed, only disconnected
         * both ways.
         */
        disconnect (d_ptr->m_Applet, 0, this, 0);
        disconnect (this, 0, d_ptr->m_Applet, 0);
        // FIXME: I think this would not be a good idea, we can not disconnect 
        // all functions, because for example we will loose hide/show signals.
        // And who knows what else are we going to connect in the future.
        // this->disconnect ();
    }

    d_ptr->m_Applet = applet;

    /*
     * If we have a applet object we can construct a widget for that and then
     * we can connect some signals.
     */
    if (d_ptr->m_Applet) {
        // FIXME: This might cause a race condition? What if the applet sends
        // a signal when we are not connected yet?
        constructRealWidget (d_ptr->m_Applet->widgetTypeID());
        /*
         * This will count the activations and activate the applet.
         */
        connect (this, SIGNAL (clicked()), 
                d_ptr->m_Applet, SLOT (slotClicked()));
        /*
         * This will follow the breiaf changes on the UI.
         */
        connect (d_ptr->m_Applet, SIGNAL (briefChanged()), 
                this, SLOT (updateContents()));
    }
}

void 
DcpBriefWidget::retranslateUi ()
{
    if (d_ptr->m_Applet) {
        d_ptr->m_RealWidget->setText1 (applet()->metadata()->text1());
        updateContents ();
    }
}

DcpButtonImage * 
DcpBriefWidget::constructImage (
        const DcpAppletObject *applet)
{
    DcpButtonImage *image = new DcpButtonImage (this);

    if (applet) {
        image->setImageName (applet->imageName());
    }

    return image;
}

DcpButtonToggle *
DcpBriefWidget::constructToggle (
        const DcpAppletObject *applet)
{
    DcpButtonToggle *toggle = new DcpButtonToggle (this);

    if (applet) {
        toggle->setSmallToggle (applet->toggle());
        toggle->setIconId (applet->toggleIconId());
        connect (toggle, SIGNAL (smallToggled (bool)),
             applet, SLOT (setToggle (bool)));
    }

    return toggle;
}

void 
DcpBriefWidget::updateContents ()
{
    if (!d_ptr->m_Applet)
        return;

    // for all:
    d_ptr->m_RealWidget->setText2 (d_ptr->m_Applet->text2()); 
    
    // toggle specific:
    DcpButtonToggle *toggle = qobject_cast<DcpButtonToggle*>
        (d_ptr->m_RealWidget);
    if (toggle) {
        toggle->setSmallToggle (d_ptr->m_Applet->toggle());
        toggle->setIconId (d_ptr->m_Applet->toggleIconId());
    } 
    
    // image specific:
    DcpButtonImage *image = qobject_cast<DcpButtonImage*>(d_ptr->m_RealWidget);
    if (image) {
        image->setImageName (d_ptr->m_Applet->imageName());
    }
}

void 
DcpBriefWidget::showEvent (
        QShowEvent *event)
{
    Q_UNUSED (event);
    Q_ASSERT (d_ptr->m_RealWidget);

    if (d_ptr->m_Hidden) { 
        // prevents multiple showEvents coming
        d_ptr->m_Hidden = false;

        connect (d_ptr->m_RealWidget, SIGNAL(clicked()), 
                this, SIGNAL(clicked()));

        if (d_ptr->m_Applet)
            connect (d_ptr->m_Applet, SIGNAL (briefChanged ()), 
                this, SLOT (updateContents()));

        updateContents();
    }
}

void 
DcpBriefWidget::hideEvent (
        QHideEvent     *event)
{
    Q_UNUSED (event);
    Q_ASSERT (d_ptr->m_RealWidget);

    if (!d_ptr->m_Hidden) {// prevents multiple hideEvents coming
        d_ptr->m_Hidden = true;

        disconnect (d_ptr->m_RealWidget, SIGNAL(clicked()), 
                this, SIGNAL(clicked()));

        if (d_ptr->m_Applet)
            disconnect (d_ptr->m_Applet, SIGNAL (briefChanged()), 
                this, SLOT (updateContents()));
    }
}

