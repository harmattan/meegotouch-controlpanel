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
#include <QGraphicsGridLayout>
#include <QVariant>

#include "dcpappletdb.h"

static const QString subtitleObjectName = "CommonSubTitleInverted";
static const QString singleTitleObjectName = "CommonSingleTitleInverted";
static const QString iconObjectName = "CommonMainIcon";
static const QString drillDownObjectName = "CommonDrillDownIcon";
static const QString toggleObjectName = "CommonSwitchInverted";
static const QString sliderObjectName = "CommonSliderInverted";

DcpContentItemPrivate::DcpContentItemPrivate ():
    m_Applet (0),
    m_Metadata (0),
    m_Hidden (true),
    m_LayoutIsToBeChanged (true),
    m_ImageW (0),
    m_DrillImage (0),
    m_Text1W (0),
    m_Text2W (0),
    m_Help (0),
    m_ButtonW (0),
    m_Slider (0),
    m_Spacer (0)
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
    setStyleName ("CommonPanelInverted");
    setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Fixed);
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
    bool result = applet() && !applet()->text2().isEmpty();
    return result;
}

bool
DcpContentItem::isChecked() const
{
    return applet() && applet()->toggle();
}

void
DcpContentItem::ensureLayoutIsCreated (QGraphicsGridLayout*& grid)
{
    // create the layout:
    grid = static_cast<QGraphicsGridLayout*>(this->layout());
    if (!grid) {
        grid = new QGraphicsGridLayout (this);
        grid->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Fixed);
        grid->setContentsMargins (0,0,0,0);
        grid->setSpacing(0);
        d_ptr->m_LayoutIsToBeChanged = true;
    }
}

void
DcpContentItem::ensureImageIsCreated()
{
    // create / free up image:
    if (widgetType() == DcpWidgetType::Image)
     {
        MImageWidget* &image = d_ptr->m_ImageW;
        if (!image) {
            image = new MImageWidget();
            image->setStyleName (iconObjectName);
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
DcpContentItem::ensureSliderIsCreated()
{
    // create / free up image:
    if (widgetType() == DcpWidgetType::Slider)
     {
        MSlider* &slider = d_ptr->m_Slider;
        if (!slider) {
            slider = new MSlider();
            slider->setStyleName (sliderObjectName);
            slider->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Fixed);
            slider->setMaximumWidth (-1);
            connect(slider, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));

            // min and max icons:
            QString image = metadata()->sliderLeftImage();
            if (!image.isEmpty()) {
                slider->setMinLabelIconID (image);
                slider->setMinLabelVisible (true);
            } else {
                slider->setMinLabelVisible (false);
            }
            image = metadata()->sliderRightImage();
            if (!image.isEmpty()) {
                slider->setMaxLabelIconID (image);
                slider->setMaxLabelVisible (true);
            } else {
                slider->setMaxLabelVisible (false);
            }

            d_ptr->m_LayoutIsToBeChanged = true;
        }

        // TODO XXX: it would be better to only update the value here
        slider->setRange(applet()->minValue(), applet()->maxValue());
        slider->setSteps(applet()->sliderSteps());
        slider->setValue(applet()->value().toInt());

    } else {
        if (d_ptr->m_Slider) {
            delete d_ptr->m_Slider;
            d_ptr->m_Slider = 0;
            d_ptr->m_LayoutIsToBeChanged = true;
        }
    }
}

void
DcpContentItem::onToggleChanged (bool toggle)
{
    dcp_failfunc_unless (applet());
    applet()->setToggle (toggle);
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
            button->setStyleName (toggleObjectName);
            button->setCheckable(true);
            connect (button, SIGNAL (toggled(bool)),
                     this, SLOT(onToggleChanged(bool)));
            d_ptr->m_LayoutIsToBeChanged = true;

            // clicking on the item is disabled (only toggle is clickable)
            if (!metadata() || !metadata()->hasMainView()) {
                setAcceptedMouseButtons (Qt::NoButton);
            }
        }
        // update switch state:
        button->setChecked (isChecked());
    } else {
        if (d_ptr->m_ButtonW) {
            delete d_ptr->m_ButtonW;
            d_ptr->m_ButtonW = 0;
            d_ptr->m_LayoutIsToBeChanged = true;

            // clicking on the item is enabled
            if (!metadata() || metadata()->hasMainView()) {
                setAcceptedMouseButtons (
                        Qt::LeftButton | Qt::RightButton | Qt::MidButton |
                        Qt::XButton1 | Qt::XButton2
                );
            }
        }
    }
}

void
DcpContentItem::ensureHelpIsCreated()
{
    QString helpId = helpID();
    MHelpButton* &help = d_ptr->m_Help;

    if (helpId.isEmpty()) {
        if (help) {
            // delete help button:
            delete help;
            help = 0;
            d_ptr->m_LayoutIsToBeChanged = true;
        }

    } else {
        if (!help) {
            // FIXME: this will be MMHelpButton once the feature got into libmeegotouch
            help = new MHelpButton(helpID());
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
    dcp_failfunc_unless (metadata());
    QString text2 = this->subtitle();

    // create the text widgets:
    if (!d_ptr->m_Text1W) {
        d_ptr->m_Text1W = new MLabel();
        d_ptr->m_LayoutIsToBeChanged = true;
        d_ptr->m_Text1W->setStyleName(singleTitleObjectName);
        d_ptr->m_Text1W->setAlignment (Qt::AlignBottom);
    }
    if (!d_ptr->m_Text2W) {
        d_ptr->m_Text2W = new MLabel();
        d_ptr->m_Text2W->setStyleName(subtitleObjectName);

        d_ptr->m_LayoutIsToBeChanged = true;
    }

    Qt::Alignment text2Align =
        metadata()->textOrientation() == Qt::Horizontal ?
        Qt::AlignRight | Qt::AlignTop : Qt::AlignTop;
    if (d_ptr->m_Text2W->alignment() != text2Align) {
        // this means that the text orientation has changed,
        // so we will need to relayout
        d_ptr->m_Text2W->setAlignment (text2Align);
        d_ptr->m_LayoutIsToBeChanged = true;
    }

    // update their texts:
    d_ptr->m_Text1W->setText (title());
    d_ptr->m_Text2W->setText (text2);
}


void
DcpContentItem::ensureWidgetsAreLayouted()
{
    dcp_failfunc_unless (metadata());

    // if there is no layout change do not do anything:
    if (!d_ptr->m_LayoutIsToBeChanged) return;
    d_ptr->m_LayoutIsToBeChanged = false;

    // we create the main layout if it is not yet created:
    QGraphicsGridLayout* grid;
    ensureLayoutIsCreated(grid);

    // clear the layout:
    for (int i=grid->count()-1; i>=0; i--) {
        grid->removeAt(i);
    }

    // layout the items again:
    int textX = d_ptr->m_ImageW ? 1 : 0;
    bool isTextHorizontal = metadata()->textOrientation() == Qt::Horizontal;
    int textLinesCount = d_ptr->m_Slider ? 1 : 2;
    if (d_ptr->m_ImageW) {
        grid->addItem (d_ptr->m_ImageW, 0,0,
                       textLinesCount, 1, Qt::AlignCenter);
    }
    // slider does not have the labels:
    if (!d_ptr->m_Slider) {
        if (!isTextHorizontal) {
            grid->addItem (d_ptr->m_Text1W, 0, textX, Qt::AlignBottom);
            grid->addItem (d_ptr->m_Text2W, 1, textX, Qt::AlignTop);
            if (d_ptr->m_Spacer) {
                d_ptr->m_Spacer->deleteLater();
                d_ptr->m_Spacer = 0;
            }
        } else {
            // this hack lets the labels start at the same y even in horizontal mode
            if (!d_ptr->m_Spacer) d_ptr->m_Spacer = new MLabel("");
            grid->addItem (d_ptr->m_Text1W, 0, textX, Qt::AlignBottom);
            grid->addItem (d_ptr->m_Text2W, 0, textX+1, Qt::AlignBottom);
            grid->addItem (d_ptr->m_Spacer, 1, textX, 1, 2, Qt::AlignTop);
            textX++;
        }
    } else {
        grid->addItem (d_ptr->m_Slider, 0, textX, Qt::AlignCenter);
    }

    int toggleX = textX+1;
    if (d_ptr->m_Help) {
        grid->addItem (d_ptr->m_Help, 0, toggleX,
                       textLinesCount, 1, Qt::AlignCenter);
        toggleX++;
    }
    if (d_ptr->m_ButtonW) {
        grid->addItem (d_ptr->m_ButtonW, 0, toggleX,
                       textLinesCount, 1, Qt::AlignCenter);
        toggleX++;
    }

    if (!d_ptr->m_ButtonW && !d_ptr->m_Slider) {
        if (!d_ptr->m_DrillImage) {
            d_ptr->m_DrillImage =
                new MImageWidget("icon-m-common-drilldown-arrow-inverse", this);
            d_ptr->m_DrillImage->setStyleName(drillDownObjectName);
        }

        grid->addItem(d_ptr->m_DrillImage, 0, toggleX, textLinesCount, 1);
        grid->setAlignment(d_ptr->m_DrillImage, Qt::AlignVCenter | Qt::AlignRight);
    } else {
        delete d_ptr->m_DrillImage;
    }
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
    ensureSliderIsCreated();

    // we set them in the layout correctly
    ensureWidgetsAreLayouted();
}

QString
DcpContentItem::title() const
{
    if (applet()) {
        if (widgetType() == DcpWidgetType::Slider) return QString();
        return applet()->text1();
    }
    if (d_ptr->m_Metadata) return d_ptr->m_Metadata->text1();
    return QString();
}

QString
DcpContentItem::subtitle() const
{
    if (applet()) {
        if (widgetType() == DcpWidgetType::Slider) return QString();
        return applet()->text2();
    }
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
    dcp_failfunc_unless (metadata());

    /*
     * Activate the applet if it has a mainview.
     */
    if (metadata()->hasMainView()) {
        if (applet()) {
            applet()->slotClicked ();
        }
    }
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
    // we have nothing to update:
    if (!d_ptr->m_ImageW) return;

    // ----------- image specific: -------------
    if (widgetType() == DcpWidgetType::Image) {
        dcp_failfunc_unless (metadata());
        QString source = applet() ? applet()->iconName()
                                  : metadata()->imageName();
        qDebug ("Image %s from %s", qPrintable(source),
                qPrintable(metadata()->name()));

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
    dcp_failfunc_unless (d_ptr->m_ImageW);
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
    dcp_failfunc_unless (d_ptr->m_ImageW);

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
    d_ptr->m_TDriverID = mattid;
}

QString DcpContentItem::mattiID () const
{
    return d_ptr->m_TDriverID;
}

void DcpContentItem::setTDriverID (const QString& tdriverid)
{
    d_ptr->m_TDriverID = tdriverid;
}

QString DcpContentItem::TDriverID () const
{
    return d_ptr->m_TDriverID;
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

void DcpContentItem::sliderChanged(int value)
{
    if (applet()) applet()->setValue(QVariant(value));
}

