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
#include <DcpSingleComponent>
#include <DcpMainCategory>
#include <Pages>
#include <DcpApplet>
#include <QGraphicsLinearLayout>
#include <MContainer>
#include <QTimer>

#include "dcpcategorycomponent.h"
#include "dcpappletbuttons.h"
#include "dcpremotebriefreceiver.h"
#include "maintranslations.h"

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
#ifdef MOSTUSED
    m_RecentlyComp (0),
#endif
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
#ifdef MOSTUSED
        m_RecentlyComp->startLoading();
#endif
        return;
    }

#ifdef MOSTUSED
    m_RecentlyComp->startLoading();
#endif
    m_HasContent = true;

    emit firstShown ();
    QTimer::singleShot (750, this, SLOT(realShown()));
}

// unfortunately appeared signal comes before the page becomes visible on
// the screen so this function gets called after a delay to start some heavier
void DcpMainPage::realShown ()
{
    // this loads the helper process a little bit earlier so that it can preload
    // some applets
    DcpRemoteBriefReceiver::instance ();

    // this adds the MainPage category if needed:
    DcpAppletButtons* category =
        new DcpAppletButtons (&DcpMain::mainPageCategory);
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

#ifdef MOSTUSED
    m_OtherComp = new MContainer();
#endif
    DcpMainCategory *otherCategories = new DcpMainCategory(
            0,
            DcpMain::otherCategoriesTitleId);
    for (int i = 0;; i++) {
        DcpSingleComponent *button;
        const DcpCategoryInfo  *info;

        info = &DcpMain::CategoryInfos[i];
        if (info->titleId == 0)
             break;

        button = new DcpSingleComponent(otherCategories, info->titleId,
                                        qtTrId(info->titleId), info->iconId, qtTrId(info->subtitleId));
        button->setSubPage(PageHandle(info->subPageId, info->titleId));
        otherCategories->appendWidget(button);
        m_CategoryButtons.append(button);
    }

#ifdef MOSTUSED
    m_OtherComp->setCentralWidget(otherCategories);
    /*
     * Creating the most recent used items.
     * Use
     * # gconftool-2 --recursive-unset /apps/duicontrolpanel/usagecount
     * to test this piece of code.
     */
    m_RecentlyComp = new DcpCategoryComponent (0, &DcpMain::mostUsedCategory,
                                               centralWidget());

#ifdef PROGRESS_INDICATOR
    // show progress indicator
    connect (m_RecentlyComp, SIGNAL (loadingFinished()),
             this, SLOT (onLoadingFinished()));
    setProgressIndicatorVisible (true);
#endif

    if (!m_RecentlyComp->getItemCount()) {
        m_RecentlyComp->hide();
    } else {
        mainLayout ()->addItem (m_RecentlyComp);
    }
    layout->addItem(m_OtherComp);
#else // MOSTUSED
    layout->addItem(otherCategories);
#endif // MOSTUSED
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
    setTitle (qtTrId(DcpMain::settingsTitleId));
    setTitleLabel ();

#ifdef MOSTUSED
    /*
     * We always retranslate the 'most used' category, see NB #156882.
     */
    if (m_RecentlyComp) {
        m_RecentlyComp->retranslateUi ();
    }

    m_OtherComp->setTitle(qtTrId(DcpMain::otherCategoriesTitleId));
#endif

    for (int i=0; i<m_CategoryButtons.count(); i++) {
        DcpSingleComponent* comp = m_CategoryButtons.at(i);
        comp->setTitle(qtTrId(DcpMain::CategoryInfos[i].titleId));
        comp->setSubtitle(qtTrId(DcpMain::CategoryInfos[i].subtitleId));
    }
}


void
DcpMainPage::reload ()
{
    DCP_DEBUG ("WARNING: RELOADING");
#ifdef MOSTUSED
     /*
     * Refreshing the 'most recently used' category. This category category will
     * be turned off when it just become empty (a highly unlikely event), and
     * will be turned on if it was empty and now become non-empty.
     */
    if (m_RecentlyComp) {
        bool was_visible;

        was_visible = m_RecentlyComp->getItemCount() != 0;

        m_RecentlyComp->reload ();
        bool should_be_visible = m_RecentlyComp->getItemCount() != 0;

        /*
         * If the 'most recetly used' category is empty we hide it, if not empty
         * we show it.
         */
        if (!should_be_visible && was_visible) {
            mainLayout ()->removeItem (m_RecentlyComp);
            m_RecentlyComp->hide();
        } else if (should_be_visible && !was_visible) {
            mainLayout ()->insertItem (0, m_RecentlyComp);
            m_RecentlyComp->show();
            m_RecentlyComp->retranslateUi ();
        }
    }
#endif 
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

