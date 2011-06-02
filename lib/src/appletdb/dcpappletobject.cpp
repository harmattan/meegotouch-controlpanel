/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include <MLocale>

#include "dcpappletobject.h"
#include "dcpappletobject_p.h"
#include "dcpappletmetadata.h"
#include "dcpapplet.h"
#include "dcpwidgettypes.h"
#include "dcpbrief.h"
#include "dcpappletif.h"
#include "dcpwidget.h"

#include <QTime>
#include "dcpdebug.h"


DcpAppletObjectPrivate::DcpAppletObjectPrivate ():
    m_Brief (0)
{
}

DcpAppletObjectPrivate::~DcpAppletObjectPrivate ()
{
    if (m_Brief)
        delete m_Brief;
}


DcpAppletObject::DcpAppletObject (DcpAppletMetadata *metadata):
      DcpAppletPlugin (metadata),
      d_ptr (new DcpAppletObjectPrivate)
{
}

DcpAppletObject::DcpAppletObject (DcpAppletMetadata *metadata, bool tryLoad):
      DcpAppletPlugin (metadata, tryLoad),
      d_ptr (new DcpAppletObjectPrivate)
{
}

DcpAppletObject::~DcpAppletObject ()
{
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

            // invalid marks for us that the type is specified in the .desktop
            // instead
        } else if (retval != DcpWidgetType::BriefInvalid) {
            /* FIXME: for supporting old api,
             * please remove ones deprecated ids are removed */
            DCP_WARNING ("%s: brief->widgetTypeID () returned a DEPRECATED id"
                         ", please use DcpWidgetType::* instead", qPrintable(text1()));
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

    return Qt::AlignLeft;
}

bool 
DcpAppletObject::toggle () const
{
    if (brief()) {
        return brief()->toggle ();
    }

    qDebug() << Q_FUNC_INFO << "no brief"; 
    return false;
}

QString
DcpAppletObject::text1 () const
{
    QString text1;

    DcpAppletIf* applet = this->applet();
    DcpBrief* brief = this->brief();

    // use DcpBrief::titleText() if specified:
    if (brief) {
        text1 = brief->titleText();
        if (!text1.isEmpty()) return text1;
    }

    if (applet) {
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
    QString text2;
    if (brief()) text2 = brief()->valueText();
    if (text2.isNull()) text2 = metadata()->text2();
    return text2;
}

/*!
 * Returns the help id of the applet. Value which comes from DcpBrief overrides
 * the value from the desktop file.
 */
QString
DcpAppletObject::helpId () const
{
    QString result = briefVersion() >= 5 ? brief()->helpId() : QString();
    if (result.isNull()) result = metadata()->helpId();
    return result;
}


/*!
 * Returns the icon name for the applet by calling the DcpBrief::icon() or
 * DcpBrief::image() virtual method.
 * If the applet returns the empty string (default implementation) the
 * method will return the icon name provided in the desktop file.
 */
QString 
DcpAppletObject::iconName() const
{
    QString retval;

    if (brief()) {
        retval = brief()->icon();
        if (retval.isEmpty()) {
            retval = brief()->image();
        }
    }

    if (retval.isEmpty())
        retval = metadata()->imageName();

    DCP_DEBUG ("Returning %s", DCP_STR(retval));
    return retval;
}

/*!
 * Same as iconName()
 */
QString 
DcpAppletObject::imageName() const
{
    return iconName();
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
 * \details This slot will request activation of an other applet.
 * (Emits the requestPluginActivation() signal.
 */
bool 
DcpAppletObject::activatePluginByName (
        const QString &appletName) const
{
    // FIXME unfortunately could not remove const yet because it would be ABI break
    emit const_cast<DcpAppletObject*>(this)->requestPluginActivation (appletName);
    return true;
}

void 
DcpAppletObject::setToggle(bool checked)
{
    if (brief()) {
        brief()->setValue (QVariant(checked));
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
        const_cast<DcpAppletObject*>(this)->setBrief (
                applet()->constructBrief (getMainWidgetId()));
//        qDebug ("created brief for %s", qPrintable(text1()));
    }

    return d_ptr->m_Brief;
}

void
DcpAppletObject::setBrief (DcpBrief* brief)
{
    d_ptr->m_Brief = brief;
    if (brief != 0) {
        connect (brief, SIGNAL (valuesChanged ()), 
                this, SIGNAL (briefChanged ()));
        connect (brief, SIGNAL (activateSignal ()), 
                this, SLOT (activateSlot ()));
    }
}



/*!
 * This slot will 1) count the activations for the 'most used' category 2)
 * re-enable if the applet is disabled and 3) send the activate() signal so
 * thath the applet will be loaded and shown.
 */
void 
DcpAppletObject::slotClicked ()
{
#ifdef MOSTUSED
    metadata()->incrementUsage();
#endif

    if (metadata()->isDisabled()) {
        DCP_DEBUG ("Enabling debug.");
        metadata()->setDisabled (false);
    }

    activateSlot();
}

void
DcpAppletObject::activateSlot (int pageId)
{
    DcpDebug::start("activate_applet");
    DCP_DEBUG ("Emitting activate(%d)", pageId);
    emit activate(pageId);
}

int DcpAppletObject::minValue() const
{
    if (brief())
	return brief()->minValue();
    else
        return 0;
}

int DcpAppletObject::maxValue() const
{
    if (briefVersion()>=8) {
        return brief()->maxValue();
    } else {
        return 100;
    }
}

int DcpAppletObject::sliderSteps() const
{
    if (briefVersion()>=8) {
        return brief()->sliderSteps();
    } else {
        return 0;
    }
}

void DcpAppletObject::setValue(const QVariant& value)
{
    if (briefVersion()>=8) {
        return brief()->setValue(value);
    }
}

QVariant DcpAppletObject::value() const
{
    if (briefVersion() >= 8) {
        return brief()->value();
    }
    return QVariant();
}

/*! \brief Version of the DcpBrief of the applet.
 *
 * Similar to interfaceVersion(), except that this function returns the
 * version of the DcpBrief instead of the applet.
 * -1 if the applet does not have a brief, but
 * big enough if the appletObject does not have an applet, but has a brief.
 */
int DcpAppletObject::briefVersion () const
{
    if (!brief()) return -1;
    return applet() ? interfaceVersion() : 999999;
}

