/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of mcontrolpanel.
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

#include "dcpcontentitem.h"
#include "dcpcontentitem_p.h"

#include "dcpdebug.h"
#include <MGridLayoutPolicy>
#include <MLayout>

#include "dcpappletdb.h"

static const QString titleObjectName = "CommonTitle";
static const QString subtitleObjectName = "CommonSubTitle";
static const QString singleTitleObjectName = "CommonSingleTitle";
static const QString iconObjectName = "CommonMainIcon";
static const QString toggleObjectName = "CommonSwitch";

DcpContentItemPrivate::DcpContentItemPrivate ():
    m_Applet (0),
    m_Metadata (0),
    m_Hidden (true),
    m_LayoutIsToBeChanged (true),
    m_ImageW (0),
    m_Text1W (0),
    m_Text2W (0),
    m_Help (0),
    m_Spacer (0),
    m_ButtonW (0)
{
}

/*
 * Stuff for the DcpContentItem class.
 */
DcpContentItem::DcpContentItem (
        DcpAppletObject *applet,
        QGraphicsItem   *parent):
    MListItem (parent),
    d_ptr (new DcpContentItemPrivate)
{
    connect (this, SIGNAL (clicked()), this, SLOT (onClicked()));
    setObjectName ("CommonPanel");
    setApplet (applet);
}


DcpContentItem::~DcpContentItem ()
{
    delete d_ptr;
}

int
DcpContentItem::widgetType() const
{
    if (d_ptr->m_Applet) {
        return d_ptr->m_Applet->widgetTypeID();
    } else if (d_ptr->m_Metadata) {
        return DcpWidgetType::Label;
    } else {
        return DcpWidgetType::BriefInvalid;
    }
}

bool
DcpContentItem::hasTwoTextLines() const
{
    return applet() && !applet()->text2().isEmpty();
}

bool
DcpContentItem::isChecked() const
{
    return applet() && applet()->toggle();
}

void
DcpContentItem::ensureLayoutIsCreated (MLayout*& layout,
                                       MGridLayoutPolicy*& grid)
{
    // create the layout:
    layout = static_cast<MLayout*>(this->layout());
    if (!layout) {
        layout = new MLayout(this);
        grid = new MGridLayoutPolicy(layout);
        layout->setContentsMargins (0,0,0,0);
        grid->setSpacing(0);
        d_ptr->m_LayoutIsToBeChanged = true;
    } else {
        grid = static_cast<MGridLayoutPolicy*>(
                layout->registeredPolicies().at(0));
    }
}

void
DcpContentItem::ensureImageIsCreated()
{
    // create / free up image:
    if (widgetType() == DcpWidgetType::Image) {
        MImageWidget* &image = d_ptr->m_ImageW;
        if (!image) {
            image = new MImageWidget();
            image->setObjectName (iconObjectName);
            image->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);
            d_ptr->m_LayoutIsToBeChanged = true;
        }
        updateImage();
    } else {
        if (d_ptr->m_ImageW) {
            delete d_ptr->m_ImageW;
            d_ptr->m_ImageW = 0;
            d_ptr->m_LayoutIsToBeChanged = true;
        }
        d_ptr->m_ImageName = "";
    }
}

void
DcpContentItem::ensureToggleIsCreated()
{
    // create / free up toggle:
    if (widgetType() == DcpWidgetType::Toggle) {
        MButton* &button = d_ptr->m_ButtonW;
        if (!button) {
            button = new MButton();
            button->setViewType(MButton::switchType);
            button->setObjectName (toggleObjectName);
            button->setCheckable(true);
            connect (button, SIGNAL (clicked(bool)),
                     applet(), SLOT(setToggle(bool)));
            d_ptr->m_LayoutIsToBeChanged = true;
        }
        // update switch state:
        button->setChecked (isChecked());
    } else {
        if (d_ptr->m_ButtonW) {
            if (applet()) {
                disconnect (d_ptr->m_ButtonW, SIGNAL (clicked(bool)),
                            applet(), SLOT(setToggle(bool)));
            }
            delete d_ptr->m_ButtonW;
            d_ptr->m_ButtonW = 0;
            d_ptr->m_LayoutIsToBeChanged = true;
        }
    }
}

void
DcpContentItem::ensureHelpIsCreated()
{
    QString helpId = helpID();
    HelpButton* &help = d_ptr->m_Help;

    if (helpId.isEmpty()) {
        if (help) {
            // delete help button:
            delete help;
            help = 0;
            d_ptr->m_LayoutIsToBeChanged = true;
        }

    } else {
        if (!help) {
            // FIXME: this will be MHelpButton once the feature got into libmeegotouch
            help = new HelpButton(helpID());
            help->setViewType(MButton::iconType);
            help->setIconID ("icon-m-content-description");
            d_ptr->m_LayoutIsToBeChanged = true;

        } else {
            help->setPageID (helpID());
        }
    }
}

void
DcpContentItem::ensureTextsAreCreated()
{
    QString text2 = this->subtitle();

    // create the text widgets:
    if (!d_ptr->m_Text1W) {
        d_ptr->m_Text1W = new MLabel();
        // TODO maybe we could find a better solution than using the objectnames
        // of the elements in MBasicListItem, because it can break in the future
        // if MBasicListItem changes
        d_ptr->m_Text1W->setObjectName(text2.isEmpty() ? singleTitleObjectName
                                       : titleObjectName);
        d_ptr->m_LayoutIsToBeChanged = true;
    }
    if (!d_ptr->m_Text2W) {
        d_ptr->m_Text2W = new MLabel();
        d_ptr->m_Text2W->setObjectName(subtitleObjectName);
        d_ptr->m_LayoutIsToBeChanged = true;
    }
    if (!d_ptr->m_Spacer) {
        d_ptr->m_Spacer = new QGraphicsWidget();
    }

    // update their texts:
    d_ptr->m_Text1W->setText (title());
    if (d_ptr->m_Text2W->text().isEmpty() != text2.isEmpty()) {
        d_ptr->m_Text1W->setObjectName(text2.isEmpty() ? singleTitleObjectName
                                       : titleObjectName);
        d_ptr->m_LayoutIsToBeChanged = true;
    }
    d_ptr->m_Text2W->setText (text2);
}


void
DcpContentItem::ensureWidgetsAreLayouted()
{
    // if there is no layout change do not do anything:
    if (!d_ptr->m_LayoutIsToBeChanged) return;
    d_ptr->m_LayoutIsToBeChanged = false;

    // we create the main layout if it is not yet created:
    MLayout* layout;
    MGridLayoutPolicy* grid;
    ensureLayoutIsCreated(layout, grid);

    // clear the layout:
    for (int i=layout->count()-1; i>=0; i--) {
        layout->removeAt(i);
    }
    Q_ASSERT (layout->count() == 0);
    Q_ASSERT (grid->count() == 0);

    // layout the items again:
    int textX = d_ptr->m_ImageW ? 1 : 0;
    int textLinesCount = hasTwoTextLines() ? 2 : 1;
    Qt::Alignment text1Align =
        hasTwoTextLines() ? Qt::AlignBottom : Qt::AlignVCenter;

    if (d_ptr->m_ImageW) {
        grid->addItem (d_ptr->m_ImageW, 0,0,
                       textLinesCount+1, 1, Qt::AlignCenter);
    }
//    grid->addItem(new QGraphicsWidget(), 0, textX);
    grid->addItem (d_ptr->m_Text1W, 0, textX, text1Align);
    if (hasTwoTextLines()) {
        grid->addItem (d_ptr->m_Text2W, 1, textX, Qt::AlignTop);
        grid->addItem (d_ptr->m_Spacer, textLinesCount, textX);
        d_ptr->m_Text2W->show();
    } else {
        d_ptr->m_Spacer->hide();
        d_ptr->m_Text2W->hide();
    }
    int toggleX = textX+1;
    if (d_ptr->m_Help) {
        grid->addItem (d_ptr->m_Help, 0, toggleX,
                       textLinesCount+1, 1, Qt::AlignCenter);
        toggleX++;
    }
    if (d_ptr->m_ButtonW) {
        grid->addItem (d_ptr->m_ButtonW, 0, toggleX,
                       textLinesCount+1, 1, Qt::AlignCenter);
        toggleX++;
    }
    MImageWidget *drillImage = new MImageWidget("icon-m-common-drilldown-arrow", this);
    drillImage->setStyleName("CommonMainIcon");
    grid->addItem(drillImage, 0, toggleX, textLinesCount+1, 1);
    grid->setAlignment(drillImage, Qt::AlignVCenter | Qt::AlignRight);
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
    // this markes that readding the items to the layout is not yet
    // necessery. The ensure functions changes it to true if they detected the
    // need for it
    d_ptr->m_LayoutIsToBeChanged = false;

    // we create the widgets (if not created yet)
    // and update their contents if necessery
    ensureHelpIsCreated();
    ensureImageIsCreated();
    ensureToggleIsCreated();
    ensureTextsAreCreated();

    // we set them in the layout correctly
    ensureWidgetsAreLayouted();
}

QString
DcpContentItem::title() const
{
    if (applet()) return applet()->text1();
    if (d_ptr->m_Metadata) return d_ptr->m_Metadata->text1();
    return QString();
}

QString
DcpContentItem::subtitle() const
{
    if (applet()) return applet()->text2();
    return QString();
}

DcpAppletObject *
DcpContentItem::applet() const
{
    return d_ptr->m_Applet;
}

DcpAppletMetadata *
DcpContentItem::metadata() const
{
    return d_ptr->m_Metadata;
}

void
DcpContentItem::clearAppletData ()
{
    /*
     * If we had an old applet object.
     */
    if (d_ptr->m_Applet) {
        /*
         * Metadata is owned by the applet db, so not removed, only disconnected
         * both ways, but only the signals between the two participants.
         */
        disconnect (d_ptr->m_Applet, 0, this, 0);
        disconnect (this, 0, d_ptr->m_Applet, 0);
    }
    d_ptr->m_Applet = 0;
    d_ptr->m_Metadata = 0;
}

void
DcpContentItem::setApplet (DcpAppletObject *applet)
{
    clearAppletData();
    if (applet) {
        d_ptr->m_Applet = applet;
        d_ptr->m_Metadata = applet->metadata();
    }

    /*
     * If we have a applet object we can construct a widget for that and then
     * we can connect some signals.
     */
    if (d_ptr->m_Applet) {
        // update
        constructRealWidget ();
        connect (d_ptr->m_Applet, SIGNAL (briefChanged ()),
                 this, SLOT (updateContents()));
    }
}

void DcpContentItem::onClicked ()
{
    Q_ASSERT (metadata());

    // force loading the applet in case it is not yet loaded
    if (!applet()) loadApplet();

    /*
     * This will count the activations and activate the applet.
     */
    applet()->slotClicked ();
}


void
DcpContentItem::setMetadata (DcpAppletMetadata* metadata)
{
    clearAppletData();
    d_ptr->m_Metadata = metadata;

    /*
     * If we have an applet object we can construct a widget for that
     */
    if (metadata) {
        // update
        constructRealWidget ();
    }
}

void
DcpContentItem::retranslateUi ()
{
    updateText ();
}


void
DcpContentItem::updateText ()
{
    ensureTextsAreCreated();
    ensureWidgetsAreLayouted();
}

QString DcpContentItem::imageID() const
{
    if (d_ptr->m_ImageW) return d_ptr->m_ImageW->image();
    return QString();
}

void DcpContentItem::updateImage ()
{
    // ----------- image specific: -------------
    if (widgetType() == DcpWidgetType::Image) {
        Q_ASSERT (d_ptr->m_Applet);
        QString source = d_ptr->m_Applet->iconName();
        qDebug ("Image %s from %s", qPrintable(source),
                qPrintable(d_ptr->m_Applet->metadata()->name()));

        /*
         * The image file might be big, so we need a little speed up here, otherwise
         * the paging effect is blocked when we go back to the main page.
         */
        if (source == d_ptr->m_ImageName)
            return;

        // no picture :(
        if (source.isEmpty()) return;

        // if it is a filepath, it has to be absolute, otherwise we have an id
        // which we request from the theme
        if (!source.contains('/')) {
            setImageName (source);
        } else {
            setImageFromFile (source);
        }

        d_ptr->m_ImageName = source;
    }
}

/*
 * updates all displayed datas if something changes in the brief / desktop file
 */
void
DcpContentItem::updateContents ()
{
    constructRealWidget();
}

/*!
 * sets the image with the given name (id)
 */
void
DcpContentItem::setImageName (const QString& name)
{
    Q_ASSERT (d_ptr->m_ImageW);
    d_ptr->m_ImageW->setImage (name);
}

/*!
 * sets the image based on its filepath
 */
void
DcpContentItem::setImageFromFile (const QString& fileName)
{
    bool    success;
    QImage  image;
    Q_ASSERT (d_ptr->m_ImageW);

    success = image.load (fileName);
    if (!success) {
        DCP_WARNING ("The image was not loaded from %s", DCP_STR(fileName));
        return;
    }

    d_ptr->m_ImageW->setImage (image);
}

void
DcpContentItem::showEvent (QShowEvent * event)
{
    MListItem::showEvent(event);
}

void
DcpContentItem::hideEvent (QHideEvent * event)
{
    MListItem::hideEvent(event);
}

void DcpContentItem::setMattiID (const QString& mattid)
{
    d_ptr->m_MattiID = mattid;
}

QString DcpContentItem::mattiID () const
{
    return d_ptr->m_MattiID;
}

void DcpContentItem::loadApplet()
{
    // do nothing if the metadata is already loaded:
    if (applet()) return;

    // do nothing if there is no metadata
    if (!metadata()) return;

    // load the applet:
    setApplet (DcpAppletDb::instance()->applet (metadata()->name()));
}

QString DcpContentItem::helpID() const
{
    if (applet()) return applet()->helpId();
    if (d_ptr->m_Metadata) return d_ptr->m_Metadata->helpId();
    return QString();
}

