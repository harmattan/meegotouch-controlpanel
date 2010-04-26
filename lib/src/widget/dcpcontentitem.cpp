/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpcontentitem.h"
#include "mwidgetview.h"
#include "dcpappletobject.h"
#include "dcpappletmetadata.h"
#include "dcpwidgettypes.h"
#include "dcpbutton.h"
#include "dcpbuttontoggle.h"
#include "dcpbuttonimage.h"
#include "dcpwrongapplets.h"

#include <MSceneManager>
#include <QGraphicsLinearLayout>
#include <QtDebug>

#include "dcpdebug.h"

/******************************************************************************
 * Private data class for the DcpContentItem class.
 */
class DcpContentItemPrivate {
public:
    DcpContentItemPrivate ();

    DcpAppletObject *m_Applet;
    bool m_Hidden;
};

DcpContentItemPrivate::DcpContentItemPrivate ():
    m_Applet (0),
    m_Hidden (true)
{
}

/******************************************************************************
 * Stuff for the DcpContentItem class.
 */
DcpContentItem::DcpContentItem (
        DcpAppletObject *applet,
        QGraphicsItem   *parent):
    MContentItem (MContentItem::IconAndTwoTextLabels, parent),
    d_ptr (new DcpContentItemPrivate)
{
    setApplet (applet);
}


DcpContentItem::~DcpContentItem ()
{
    delete d_ptr;
}


/*
 * Constructs the content of the DcpContentItem according to the widget type.
 * This is a separate code so the inherited classes might use other code,
 * possibly without any information about the applet variant. This way we can
 * implement internal brief widgets also.
 */
void
DcpContentItem::constructRealWidget ()
{
    int widgetTypeId = d_ptr->m_Applet->widgetTypeID();
    switch (widgetTypeId) {
        case DcpWidgetType::Image:
            DCP_DEBUG ("### DcpWidgetType::Image ###");
            constructImage ();
            break;

        case DcpWidgetType::Toggle:
            qWarning("Support for toggle type as briefwidget was removed from "
                     "controlpanel according to the latest specifications (%s)",
                     qPrintable(applet()->metadata()->name()));
        default:
            DCP_DEBUG ("### DcpWidgetType::Label ###");
            constructLabel ();
            break;
    }

    retranslateUi ();
}

DcpAppletObject *
DcpContentItem::applet() const
{
    return d_ptr->m_Applet;
}

void
DcpContentItem::setApplet (DcpAppletObject *applet)
{
    /*
     * If we had an old applet object.
     */
    if (d_ptr->m_Applet) {
        /*
         * Metadata is owned by the appletdb, so not removed, only disconnected
         * both ways, but only the signals between the two participants.
         */
        disconnect (d_ptr->m_Applet, 0, this, 0);
        disconnect (this, 0, d_ptr->m_Applet, 0);
    }

    d_ptr->m_Applet = applet;

    /*
     * If we have a applet object we can construct a widget for that and then
     * we can connect some signals.
     */
    if (d_ptr->m_Applet) {
        constructRealWidget ();
        /*
         * This will count the activations and activate the applet.
         */
        connect (this, SIGNAL (clicked()),
                d_ptr->m_Applet, SLOT (slotClicked()));
        /*
         * This will follow the breif changes on the UI.
         */
        connect (d_ptr->m_Applet, SIGNAL (briefChanged()), 
                this, SLOT (updateContents()));
    }
}

void
DcpContentItem::retranslateUi ()
{
    if (d_ptr->m_Applet) {
        updateContents ();
    }
}

void
DcpContentItem::constructLabel ()
{
//    const DcpAppletObject *applet = this->applet();
    model()->setItemStyle(SingleTextLabel);
}

void
DcpContentItem::constructImage ()
{
    constructLabel();
#if 0
    const DcpAppletObject *applet = applet();

    if (applet) {
        QString   source;
        /*
         * If the applet provides an image file name we set the image from that,
         * otherwise we try to set the image from the icon name.
         */
        source = applet->imageName();
        if (source.isEmpty()) {
            source = applet->iconName();
        }
        d_ptr->pixmap = DuiTheme::pixmap(
    }
#endif
}

/*
 * this function is a helper, it switches from two-line-mode into one-line-mode
 * and back
 */
void
DcpContentItem::invertTwoLineMode()
{
    int styl = model()->itemStyle();
    MContentItem::ContentItemStyle newstyl;
    switch (styl) {
        case IconAndTwoTextLabels:
            newstyl = IconAndSingleTextLabel;
            break;
        case SingleTextLabel:
            newstyl = TwoTextLabels;
            break;
        case IconAndSingleTextLabel:
            newstyl = IconAndTwoTextLabels;
            break;
        case TwoTextLabels:
            newstyl = SingleTextLabel;
            break;
        case IconAndSingleTextLabelVertical:
            newstyl = IconAndTwoTextLabelsVertical;
            break;
        case IconAndTwoTextLabelsVertical:
            newstyl = IconAndSingleTextLabelVertical;
            break;
        default:
            return; // do nothing bad at least :)
    }
    model()->setItemStyle(newstyl);
}

void
DcpContentItem::updateContents ()
{
    if (!d_ptr->m_Applet)
        return;

    // for all:
    QString text2 = applet()->text2();
    /*
     * if emptyness of text2 changes, we will have to switch from twolinemode,
     * so that the labels remains centered
     *
     * FIXME: this is not working, the first time determines which mode the
     * item will be in, because the widget sizes are set up at setupModel time
     * only, so currently MContentItem only supports changing the value at
     * construction time (bug/feature request to libdui if it is important)
     */
    if (text2.isEmpty() != subtitle().isEmpty()) {
        invertTwoLineMode();
    }
    setTitle (applet()->text1());
    setSubtitle (text2);

    // image specific:
#if 0
    DcpButtonImage *image = qobject_cast<DcpButtonImage*>(d_ptr->m_RealWidget);
    if (image) {
        QString   source;

        /*
         * If the applet provides an image file name we set the image from that,
         * otherwise we try to set the image from the icon name.
         */
        source = d_ptr->m_Applet->imageName();
        if (!source.isEmpty()) {
            DCP_DEBUG ("Calling image->setImageFromFile (%s)", DCP_STR(source));
            image->setImageFromFile (source);
        } else {
            source = d_ptr->m_Applet->iconName();
            DCP_DEBUG ("Calling image->setImageName (%s)", DCP_STR(source));
            image->setImageName (source);
        }
    }
#endif
}

void
DcpContentItem::showEvent (QShowEvent *event)
{
    Q_UNUSED (event);
    // TODO XXX: automatic setItemMode...

    if (d_ptr->m_Hidden) {
        // prevents multiple showEvents coming
        d_ptr->m_Hidden = false;

        if (d_ptr->m_Applet)
            connect (d_ptr->m_Applet, SIGNAL (briefChanged ()), 
                this, SLOT (updateContents()));

        updateContents();
    }
}

void
DcpContentItem::hideEvent (QHideEvent *event)
{
    Q_UNUSED (event);

    if (!d_ptr->m_Hidden) {// prevents multiple hideEvents coming
        d_ptr->m_Hidden = true;

        if (d_ptr->m_Applet)
            disconnect (d_ptr->m_Applet, SIGNAL (briefChanged()),
                this, SLOT (updateContents()));
    }
}

