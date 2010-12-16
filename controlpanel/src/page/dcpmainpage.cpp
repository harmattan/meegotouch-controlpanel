/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpmainpage.h"

#include <QtDebug>
#include <MApplication>
#include <MApplicationWindow>
#include <dcpsinglecomponent.h>
#include <dcpmaincategory.h>
#include <pages.h>
#include <DcpApplet>
#include <QGraphicsLinearLayout>
#include <MContainer>
#include <QTimer>

#include "dcpappletbuttons.h"
#include "dcpremotebriefreceiver.h"
#include "pagefactory.h"
#include "category.h"
#include "dcpcategories.h"

#include "mwidgetcreator.h"
M_REGISTER_WIDGET_NO_CREATE(DcpMainPage)

#include "../../../lib/src/dcpdebug.h"

/*!
 * \class DcpMainPage
 * \brief The main page of duicontrolpanel.
 *
 * Displays a list of the applet categories and emits a signal if one of them is
 * to be opened.  Also has a recent used items list at the top, which contains
 * buttons to directly access the most commonly used applets (without searching
 * for them in the categories.
 */
DcpMainPage::DcpMainPage() :
    DcpPage (),
    m_HasContent (false),
    m_WasHidden (false)
{
    connect (this, SIGNAL(appeared()),
            this, SLOT(shown()));
}

/*!
 * this function is called when the main page has been shown. here we start to
 * load the applets and put categoryies and brief widgets into the window, here
 * the progressive load starts.
 */
void
DcpMainPage::shown ()
{
    DCP_DEBUG ("##################################################");
    DCP_DEBUG ("### Main page has been shown #####################");
    DCP_DEBUG ("##################################################");

    if (m_HasContent) {
        if (m_WasHidden) {
            m_WasHidden = false;
            reload ();
        }
        return;
    }

    m_HasContent = true;

    QTimer::singleShot (750, this, SLOT(realShown()));
}

// unfortunately appeared signal comes before the page becomes visible on
// the screen so this function gets called after a delay to start some heavier
void DcpMainPage::realShown ()
{
    // this loads the helper process a little bit earlier so that it can preload
    // some applets
    DcpRemoteBriefReceiver* receiver = DcpRemoteBriefReceiver::instance ();

    // this preloads an applet launcher process when the receiver has finished
    connect (receiver, SIGNAL (firstConnected()),
             PageFactory::instance(), SLOT (preloadAppletLauncher()));

    // this adds the MainPage category if needed:
    DcpAppletButtons* category =
        new DcpAppletButtons (DcpCategories::instance()->mainPageCategory());
    mainLayout()->addItem (category);
}

void
DcpMainPage::hideEvent(QHideEvent*)
{
    m_WasHidden = true;
}

/*!
 * Creates the empty category containers inside the main page.
 */
void
DcpMainPage::createContent ()
{
    DCP_DEBUG ("");
    QGraphicsLinearLayout *layout;
    DcpPage::createContent ();

    layout = mainLayout ();
    Q_ASSERT(layout);

    DcpMainCategory *otherCategories = new DcpMainCategory();
    DcpCategories* categoryDb = DcpCategories::instance();
    QList<const Category*> categoryList =
        categoryDb->categoryChildren (DcpCategories::mainPageCategoryName());

    foreach (const Category *info, categoryList) {
        DcpSingleComponent *button;

        button = new DcpSingleComponent(otherCategories, info->titleId(),
                                        info->iconId(), info->subtitleId());
        button->setSubPage(PageHandle(PageHandle::APPLETCATEGORY, info->name()));
        otherCategories->appendWidget(button);
        m_CategoryButtons.append(button);
    }

    layout->addItem(otherCategories);
    retranslateUi();
}


void
DcpMainPage::onLoadingFinished ()
{
#ifdef PROGRESS_INDICATOR
    setProgressIndicatorVisible (false);
#endif
}

void
DcpMainPage::retranslateUi ()
{
    const Category* mainCategory = DcpCategories::instance()->mainPageCategory();
    setTitle (mainCategory ? mainCategory->title(): QString());
    setTitleLabel ();
}


void
DcpMainPage::reload ()
{
    /*
     * DcpBriefWidget should take care of updating their contents in showEvent
     */
    DcpPage::reload ();
}

// if clicked fast, back button can be pressed instead of close
void 
DcpMainPage::back()
{
    qApp->quit();
}

