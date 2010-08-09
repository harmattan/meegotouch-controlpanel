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

#include "mcpcontentwidget.h"
#include "mcpcontentwidget_p.h"

#include "dcpdebug.h"
#include <MGridLayoutPolicy>
#include <MLayout>


McpContentWidgetPrivate::McpContentWidgetPrivate ():
    m_Applet (0),
    m_Hidden (false),
    m_LayoutIsToBeChanged (true),
    m_ImageW (0),
    m_Text1W (0),
    m_Text2W (0),
    m_ButtonW (0)
{
}

/*
 * Stuff for the McpContentWidget class.
 */
McpContentWidget::McpContentWidget (
        DcpAppletObject *applet,
        QGraphicsItem   *parent):
    MListItem (parent),
    d_ptr (new McpContentWidgetPrivate)
{
    setApplet (applet);
}


McpContentWidget::~McpContentWidget ()
{
    delete d_ptr;
}

int
McpContentWidget::widgetType() const
{
    if (d_ptr->m_Applet) {
        return d_ptr->m_Applet->widgetTypeID();
    } else {
        return DcpWidgetType::BriefInvalid;
    }
}

bool
McpContentWidget::hasTwoTextLines() const
{
    return applet() && !applet()->text2().isEmpty();
}

bool
McpContentWidget::isChecked() const
{
    return applet() && applet()->toggle();
}

void
McpContentWidget::ensureLayoutIsCreated (MLayout*& layout,
                                       MGridLayoutPolicy*& grid)
{
    // create the layout:
    layout = static_cast<MLayout*>(this->layout());
    if (!layout) {
        layout = new MLayout(this);
        grid = new MGridLayoutPolicy(layout);
        layout->setContentsMargins (0,0,10,0); // TODO could be moved to style
        grid->setSpacing(0);
        d_ptr->m_LayoutIsToBeChanged = true;
    } else {
        grid = static_cast<MGridLayoutPolicy*>(
                layout->registeredPolicies().at(0));
    }
}

void
McpContentWidget::ensureImageIsCreated()
{
    // create / free up image:
    if (widgetType() == DcpWidgetType::Image) {
        MImageWidget* &image = d_ptr->m_ImageW;
        if (!image) {
            image = new MImageWidget();
            image->setObjectName ("ContentItemImage");
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
    }
}

void
McpContentWidget::ensureToggleIsCreated()
{
    // create / free up toggle:
    if (widgetType() == DcpWidgetType::Toggle) {
        MButton* &button = d_ptr->m_ButtonW;
        if (!button) {
            button = new MButton();
            connect (button, SIGNAL (clicked(bool)),
                     applet(), SLOT(setToggle(bool)));
            button->setViewType(MButton::switchType);
            button->setCheckable(true);
            d_ptr->m_LayoutIsToBeChanged = true;
        }
        // update switch state:
        button->setChecked (isChecked());
    } else {
        if (d_ptr->m_ButtonW) {
            delete d_ptr->m_ButtonW;
            d_ptr->m_ButtonW = 0;
            d_ptr->m_LayoutIsToBeChanged = true;
        }
    }
}

void
McpContentWidget::ensureTextsAreCreated()
{
    // create the text widgets:
    if (!d_ptr->m_Text1W) {
        d_ptr->m_Text1W = new MLabel();
        // TODO maybe we could find a better solution than using the objectnames
        // of the elements in MContentItem, because it can break in the future
        // if MContentItem changes
        d_ptr->m_Text1W->setObjectName("ContentItemTitle");
        d_ptr->m_LayoutIsToBeChanged = true;
    }
    if (!d_ptr->m_Text2W) {
        d_ptr->m_Text2W = new MLabel();
        d_ptr->m_Text2W->setObjectName("ContentItemSubtitle");
        d_ptr->m_LayoutIsToBeChanged = true;
    }

    // update their texts:
    d_ptr->m_Text1W->setText (text1());
    QString text2 = this->text2();
    if (d_ptr->m_Text2W->text().isEmpty() != text2.isEmpty()) {
        d_ptr->m_LayoutIsToBeChanged = true;
    }
    d_ptr->m_Text2W->setText (text2);
}


void
McpContentWidget::ensureWidgetsAreLayouted()
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
                       textLinesCount+2, 1, Qt::AlignCenter);
    }
    grid->addItem(new QGraphicsWidget(), 0, textX);
    grid->addItem (d_ptr->m_Text1W, 1, textX, text1Align);
    if (hasTwoTextLines()) {
        d_ptr->m_Text2W->show();
        grid->addItem (d_ptr->m_Text2W, 2, textX, Qt::AlignTop);
    } else {
        d_ptr->m_Text2W->hide();
    }
    grid->addItem(new QGraphicsWidget(), textLinesCount+1, textX);
    if (d_ptr->m_ButtonW) {
        grid->addItem (d_ptr->m_ButtonW, 0, textX+1,
                       textLinesCount+2, 1, Qt::AlignCenter);
    }
}


/*
 * Constructs the content of the McpContentWidget according to the widget type.
 * This is a separate code so the inherited classes might use other code,
 * possibly without any information about the applet variant. This way we can
 * implement internal brief widgets also.
 */
void
McpContentWidget::constructRealWidget ()
{
    // this markes that readding the items to the layout is not yet
    // necessery. The ensure functions changes it to true if they detected the
    // need for it
    d_ptr->m_LayoutIsToBeChanged = false;

    // we create the widgets (if not created yet)
    // and update their contents if necessery
    ensureImageIsCreated();
    ensureToggleIsCreated();
    ensureTextsAreCreated();

    // we set them in the layout correctly
    ensureWidgetsAreLayouted();
}

QString
McpContentWidget::text1() const
{
    if (applet()) return applet()->text1();
    return QString();
}

QString
McpContentWidget::text2() const
{
    if (applet()) return applet()->text2();
    return QString();
}

DcpAppletObject *
McpContentWidget::applet() const
{
    return d_ptr->m_Applet;
}

void
McpContentWidget::setApplet (DcpAppletObject *applet)
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
    }
}

void
McpContentWidget::retranslateUi ()
{
    if (d_ptr->m_Applet) {
        updateText ();
    }
}


void
McpContentWidget::updateText ()
{
    ensureTextsAreCreated();
    ensureWidgetsAreLayouted();
}


void McpContentWidget::updateImage ()
{
    // ----------- image specific: -------------
    if (widgetType() == DcpWidgetType::Image) {

        QString source = d_ptr->m_Applet->iconName();

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
McpContentWidget::updateContents ()
{
    if (!d_ptr->m_Applet)
        return;

    constructRealWidget();
}

/*!
 * sets the image with the given name (id)
 */
void
McpContentWidget::setImageName (const QString& name)
{
    if (d_ptr->m_ImageW) { // XXX move create here?
        d_ptr->m_ImageW->setImage (name); // FIXME XXX why is it not working???
    }
}

/*!
 * sets the image based on its filepath
 */
void
McpContentWidget::setImageFromFile (const QString& fileName)
{
    bool    success;
    QImage  image;

    success = image.load (fileName);
    if (!success) {
        DCP_WARNING ("The image was not loaded from %s", DCP_STR(fileName));
        return;
    }

    if (d_ptr->m_ImageW) { // XXX move create here?
        d_ptr->m_ImageW->setImage (image);
    }
}

void
McpContentWidget::showEvent (QShowEvent * event)
{
    if (d_ptr->m_Hidden) {
        // prevents multiple showEvents coming
        d_ptr->m_Hidden = false;

        if (d_ptr->m_Applet)
            connect (d_ptr->m_Applet, SIGNAL (briefChanged ()),
                this, SLOT (updateContents()));

        updateContents();
    }
    MListItem::showEvent(event);
}

void
McpContentWidget::hideEvent (QHideEvent * event)
{
    if (!d_ptr->m_Hidden) {// prevents multiple hideEvents coming
        d_ptr->m_Hidden = true;

        if (d_ptr->m_Applet)
            disconnect (d_ptr->m_Applet, SIGNAL (briefChanged()),
                this, SLOT (updateContents()));
    }
    MListItem::hideEvent(event);
}

void McpContentWidget::setMattiID (const QString& mattid)
{
    d_ptr->m_MattiID = mattid;
}

QString McpContentWidget::mattiID () const
{
    return d_ptr->m_MattiID;
}

