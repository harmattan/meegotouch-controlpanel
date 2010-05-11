/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include <MLocale>

#include "dcpappletobject.h"
#include "dcpappletobject_p.h"
#include "dcpappletmetadata.h"
#include "dcpapplet.h"
#include "dcpwidgettypes.h"
#include "dcpappletdb.h"
#include "dcpbrief.h"
#include "dcpappletif.h"
#include "dcpwidget.h"

#include "dcpdebug.h"



DcpAppletObjectPrivate::DcpAppletObjectPrivate ()
    : m_Brief (0)
{
}

DcpAppletObjectPrivate::~DcpAppletObjectPrivate ()
{
    if (m_Brief)
        m_Brief->deleteLater ();
}


DcpAppletObject::DcpAppletObject(DcpAppletMetadata *metadata):
      DcpAppletPlugin(metadata),
      d_ptr (new DcpAppletObjectPrivate)
{
}

DcpAppletObject::~DcpAppletObject ()
{
    DCP_DEBUG ("Destroying %p", this);
    delete d_ptr;
}

/*!
 * \brief Returns what type of brief widget shall an applet variant use.
 *
 * Gets the required brief widget type code of the applet variant. 
 */
int 
DcpAppletObject::widgetTypeID () const
{
    int         retval;

    /*
     * If we have a brief and it provides us a widget type id that is valid, we
     * can use that.
     */
    if (brief()) {
        retval = brief()->widgetTypeID ();
        if (DcpWidgetType::isIdValid(retval)) {
            DCP_DEBUG ("brief->widgetTypeID () provides a widget type.");
            return retval;
        } else {
            /* FIXME: for supporting old api,
             * please remove ones deprecated ids are removed */
            switch (retval) {
                case DCPLABELBUTTON:
                case DCPLABEL2BUTTON:
                case DCPLABEL2TOGGLE:
                    return DcpWidgetType::Toggle;
                case DCPLABEL2IMAGE:
                    return DcpWidgetType::Image;
                case DCPLABEL:
                case DCPLABEL2:
                    return DcpWidgetType::Label;
            };
        }
    }

    // return the value from the desktop file:
    retval = metadata()->widgetTypeID ();
    if (DcpWidgetType::isIdValid(retval)) {
        return retval;
    }

    /*
     * Otherwise we return the default value, simple plugins can rely on this.
     */
    DCP_DEBUG ("Using default widget type.");
    return DcpWidgetType::Label;
}

Qt::Alignment 
DcpAppletObject::align () const
{
    if (brief()){
        return brief()->align();
    }

    qWarning() << Q_FUNC_INFO << "no data"; // default
    return Qt::AlignLeft;
}

bool 
DcpAppletObject::toggle () const
{
    if (brief()) {
        return brief()->toggle ();
    }

    qWarning() << Q_FUNC_INFO << "no brief"; 
    return false;
}

QString
DcpAppletObject::text1 () const
{
    DcpAppletIf* applet = this->applet();
    if (applet) {
        // use DcpBrief::titleText() if specified:
        QString text1;

        DcpBrief* brief = this->brief();
        if (brief) {
            text1 = brief->titleText();
            if (!text1.isEmpty()) return text1;
        }

        // use DcpAppletIf::title() by default:
        // FIXME: deprecated to avoid confusion
        text1 = applet->title();
        if (!text1.isEmpty()) return text1;
    }

    /* in case the applet does not specify a title, use the one from the
     * desktop file:
     */
    return metadata()->text1();
}

QString 
DcpAppletObject::text2 () const
{
    /*
     * FIXME: This feature is not in the UI spec, we have no localization for
     * the string.
     */
    if (metadata()->isDisabled())
        return QString ("Disabled");

    return (brief() ? brief()->valueText() : metadata()->text2());
}

/*!
 * Returns the icon name for the applet by calling the DcpBrief::icon() virtual
 * method. If the applet returns the empty string (default implementation) the
 * method will return the icon name provided in the desktop file.
 */
QString 
DcpAppletObject::iconName() const
{
    QString retval;

    if (brief())
        retval = brief()->icon();

    if (retval.isEmpty())
        retval = metadata()->imageName();

    DCP_DEBUG ("Returning %s", DCP_STR(retval));
    return retval;
}

/*!
 * Returns the image file name if the applet interface provides an image file
 * name by implementing the DcpBrief::image() virtual function. If the applet
 * does not implement this virtual method returns the empty string (default
 * implementation).
 */
QString 
DcpAppletObject::imageName() const
{
    QString retval = brief() ? brief()->image() : QString();

    DCP_DEBUG ("Returning %s", DCP_STR(retval));
    return retval;
}

QString 
DcpAppletObject::toggleIconId () const
{
    return (brief() ? brief()->toggleIconId() : metadata()->toggleIconId());
}



/*!
 * \brief A slot for the inter plugin activation.
 * \param appletName The name of the applet to activate.
 * 
 * \details This slot will activate an other applet. First the function will
 * find the applet using the applet database then it will emit a signal for it,
 * so it is going to be started.
 *
 * FIXME: to be moved to DcpAppletDb ?
 */
bool 
DcpAppletObject::activatePluginByName (
        const QString &appletName) const
{
    Q_UNUSED(appletName);
    DcpAppletObject  *otherApplet;

    DCP_WARNING ("Want to start '%s'", DCP_STR (appletName));

    otherApplet = DcpAppletDb::instance()->applet (appletName);
    if (otherApplet) {
        otherApplet->activateSlot ();
        return true;
    }

    DCP_WARNING ("Applet with name '%s' not found.", DCP_STR (appletName));
    return false;
}

void 
DcpAppletObject::setToggle(bool checked)
{
    if (brief()) {
        brief()->setToggle(checked);
    } else {
        qWarning("Can not set toggle state for the applet %s",
                 qPrintable(metadata()->fileName()));
    }
}


/*!
 * \brief Calls the applet and returns the partid set for this desktop file. 
 *
 * This function will take the "DCP/Part" key and call the 
 * "int partID(const QString& partStr)" function of the plugin to get the
 * widgetId for the first/main widget. If the applet is not available the 
 * function will return -1, that is an invalid widgetId.
 */
int 
DcpAppletObject::getMainWidgetId () const
{
    if (!isAppletLoaded())
        return -1;

    return applet()->partID(metadata()->part());
}

DcpBrief *
DcpAppletObject::brief () const
{
    if (d_ptr->m_Brief == 0 && applet() != 0) {
        d_ptr->m_Brief = applet()->constructBrief (getMainWidgetId());

        if (d_ptr->m_Brief != 0) {
            connect (d_ptr->m_Brief, SIGNAL (valuesChanged ()), 
                    this, SIGNAL (briefChanged ()));
            connect (d_ptr->m_Brief, SIGNAL (activateSignal ()), 
                    this, SLOT (activateSlot ()));
        }
    }

    return d_ptr->m_Brief;
}




/*!
 * This slot will 1) count the activations for the 'most used' category 2)
 * re-enable if the applet is disabled and 3) send the activate() signal so
 * thath the applet will be loaded and shown.
 */
void 
DcpAppletObject::slotClicked ()
{
    metadata()->incrementUsage();

    if (metadata()->isDisabled()) {
        DCP_DEBUG ("Enabling debug.");
        metadata()->setDisabled (false);
    }

    activateSlot();
}

void
DcpAppletObject::activateSlot (int pageId)
{
    DCP_DEBUG ("Emitting activate(%d)", pageId);
    emit activate(pageId);
}


