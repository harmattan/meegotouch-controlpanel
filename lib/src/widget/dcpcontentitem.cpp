/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpcontentitem.h"
#include "dcpappletobject.h"
#include "dcpappletmetadata.h"
#include "dcpwidgettypes.h"

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
    int m_WidgetTypeId;
    bool m_Hidden;

    QString m_MattiID;

    // for the image widget:
    QString m_ImageName; // either the image id or path
    const QPixmap* m_Pixmap;   // the pixmap requested from MTheme if any
};

DcpContentItemPrivate::DcpContentItemPrivate ():
    m_Applet (0),
    m_WidgetTypeId (DcpWidgetType::Label),
    m_Hidden (true),
    m_Pixmap (0)
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
    releaseImage();
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
    d_ptr->m_WidgetTypeId = d_ptr->m_Applet->widgetTypeID();
    switch (d_ptr->m_WidgetTypeId) {
        case DcpWidgetType::Image:
            DCP_DEBUG ("### DcpWidgetType::Image ###");
            model()->setItemStyle(IconAndSingleTextLabel);
            break;

        case DcpWidgetType::Toggle:
            qWarning("Support for toggle type as briefwidget was removed from "
                     "controlpanel according to the latest specifications (%s)",
                     qPrintable(applet()->metadata()->name()));
        default:
            DCP_DEBUG ("### DcpWidgetType::Label ###");
            model()->setItemStyle(SingleTextLabel);
            break;
    }

    updateContents ();
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
        updateText ();
    }
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
DcpContentItem::updateText ()
{
    // --------- label specific ------------
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
}

void DcpContentItem::updateImage ()
{
    // ----------- image specific: -------------
    if (d_ptr->m_WidgetTypeId == DcpWidgetType::Image) {
        QString   source;

        /*
         * If the applet provides an image file name we set the image from that,
         * otherwise we try to set the image from the icon name.
         *
         * TODO we should clean this up. Is there a difference, or we just
         * keeping it for compatibility?
         */
        source = d_ptr->m_Applet->imageName();
        if (source.isEmpty()) {
            source = d_ptr->m_Applet->iconName();
        }

        /*
         * The image file might be big, so we need a little speed up here, otherwise
         * the paging effect is blocked when we go back to the main page.
         */
        if (source == d_ptr->m_ImageName)
            return;

        /* we release the original pixmap, if any */
        releaseImage();

        // no picture :(
        if (source.isEmpty()) return;

        // if it is a filepath, it has an extension, otherwise we have an id
        if (!source.contains('.')) {
            setImageName (source);
        } else {
            setImageFromFile (source);
        }
    }
}

/*
 * updates all displayed datas if something changes in the brief / desktop file
 */
void
DcpContentItem::updateContents ()
{
    if (!d_ptr->m_Applet)
        return;

    updateText();
    updateImage();
}

/*!
 * releases the cached image if any
 */
void
DcpContentItem::releaseImage ()
{
    const QPixmap*& pix = d_ptr->m_Pixmap;
    if (pix) {
        MTheme::releasePixmap (pix);
        pix = 0;
    }
}


/*!
 * sets the image with the given name (id)
 */
void
DcpContentItem::setImageName (const QString& name)
{
    d_ptr->m_Pixmap = MTheme::pixmap (name);
    setPixmap (*(d_ptr->m_Pixmap));
}

/*!
 * sets the image based on its filepath
 */
void
DcpContentItem::setImageFromFile (const QString& fileName)
{
    bool    success;
    QImage  image;

    success = image.load (fileName);
    if (!success) {
        DCP_WARNING ("The image was not loaded from %s", DCP_STR(fileName));
        return;
    }

    setImage (image);

    d_ptr->m_ImageName = fileName;
}

void
DcpContentItem::showEvent (QShowEvent *event)
{
    Q_UNUSED (event);

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

void DcpContentItem::setMattiID (const QString& mattid)
{
    d_ptr->m_MattiID = mattid;
}

QString DcpContentItem::mattiID () const
{
    return d_ptr->m_MattiID;
}
