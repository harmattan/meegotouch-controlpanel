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

#include "dcpappletcategorypage.h"
#include "dcpsinglecomponent.h"
#include "dcpappletbuttons.h"
#include "dcpmaincategory.h"
#include "category.h"
#include "pages.h"
#include "dcpmostused.h"
#include "dcpdebug.h"
#include "pagefactory.h"
#include "categoryutils.h"
#include "dcppageopenbutton.h"

#include <DcpAppletMetadata>
#include <DcpAppletObject>
#include "dcptranslationmanager.h"

#include <QtDebug>
#include <QGraphicsLinearLayout>
#include <QTimer>


DcpAppletCategoryPage::DcpAppletCategoryPage (
        const Category *categoryInfo) :
    DcpPage (),
    m_CategoryInfo (categoryInfo),
    m_Category (0),
    m_MostUsed (0),
    m_DelayedContent (0),
    m_Spacer (0)
{
}

DcpAppletCategoryPage::~DcpAppletCategoryPage ()
{
}

QGraphicsWidget*
DcpAppletCategoryPage::createCategories ()
{
    DcpMainCategory *otherCategories = new DcpMainCategory();
    QList<const Category*> categoryList;
    if (m_CategoryInfo) categoryList = m_CategoryInfo->children();
    if (categoryList.isEmpty()) {
        return otherCategories;
    }

    bool hasSeparator = m_CategoryInfo->hasSeparatorLine();
    if (hasSeparator &&
        m_CategoryInfo->componentOrder() == Category::AppletsFirst) {
        otherCategories->appendSeparator();
    }

    bool wasButton = false;
    foreach (const Category *info, categoryList) {
        // hide hidden categories:
        if (!CategoryUtils::isVisible (info)) continue;

        DcpTranslationManager::instance()->ensureTranslationsAreLoaded (
                info->translationCategories());

        PageHandle subPage(PageHandle::APPLETCATEGORY, info->name());
        int wtype = info->widgetType();
        QGraphicsWidget* widget = 0;
        switch (wtype) {
            case Category::WButton:
                {
                    if (!wasButton) {
                        otherCategories->appendSpacer();
                        wasButton = true;
                    }
                    DcpPageOpenButton* button =
                        new DcpPageOpenButton (subPage, info->titleId());
                    button->setTDriverID ("DcpPageOpenButton::" +
                            m_CategoryInfo->titleId() + "::" +
                            info->titleId());
                    widget = button;
                }
                break;
            case Category::WLabel:
                {
                    if (wasButton) {
                        otherCategories->appendSpacer();
                        wasButton = false;
                    }
                    DcpSingleComponent *button =
                        new DcpSingleComponent(0, info);
                    button->setSubPage(subPage);
                    widget = button;
                }
                break;
        };
        if (widget) {
            otherCategories->appendWidget(widget);
        }
    }
    if (wasButton) {
        otherCategories->appendSpacer();
        wasButton = false;
    }

    if (hasSeparator &&
        m_CategoryInfo->componentOrder() == Category::CategoriesFirst) {
        otherCategories->appendSeparator();
    }
    return otherCategories;
}

void
DcpAppletCategoryPage::mostUsedAppears ()
{
    dcp_failfunc_unless (m_MostUsed);
    QGraphicsLinearLayout* layout = mainLayout();
    dcp_failfunc_unless (layout);
    layout->insertItem (1, m_MostUsed); // TODO XXX this might be wrong
    m_MostUsed->show();
}

/*
 * Helper function which adds the "categories" and the "applets"
 * in the correct order to the layout
 *
 * if there are elements in the layout (eg. a spacer at the end),
 * then it adds them before the last element
 */
void
DcpAppletCategoryPage::addCategoryToLayoutOrdered (
        QGraphicsLinearLayout* layout,
        QGraphicsWidget* category,
        QGraphicsWidget* appletBriefs)
{
    // this hack moves the widgets out of screen until the layout sets
    // their geometry correctly. It is needed to avoid layouting flicker
    // when the first category page is popped up
    category->setGeometry (900, 0, 480, 1);
    appletBriefs->setGeometry (900, 0, 480, 1);

    // the position of the last item:
    int pos = layout->count();
    if (pos > 0) pos--;

    if (m_CategoryInfo->componentOrder() == Category::CategoriesFirst) {
        layout->insertItem (pos,category);
        layout->insertItem (pos+1,appletBriefs);
    } else {
        layout->insertItem (pos,appletBriefs);
        layout->insertItem (pos+1,category);
    }
}

void
DcpAppletCategoryPage::createContent ()
{
    // ensures that the translation for the title is loaded:
    DcpTranslationManager::instance()->ensureTranslationsAreLoaded (
                m_CategoryInfo->translationCategories());

    DcpPage::createContent ();

    m_Spacer = new QGraphicsWidget();
    m_Spacer->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_Spacer->setContentsMargins (0,0,0,0);
    m_Spacer->setMinimumHeight (1);

    if (!m_DelayedContent) {
        createBody();
    }
    retranslateUi();

    if (!m_CategoryInfo->titleStyle().isEmpty()) {
        setTitleStyleName (m_CategoryInfo->titleStyle());
    }
    mainLayout()->addItem(m_Spacer);
}

const QString 
DcpAppletCategoryPage::appletCategory() const 
{
    return m_CategoryInfo->name();
}

void
DcpAppletCategoryPage::setCategoryInfo (
        const Category *categoryInfo)
{
    m_CategoryInfo = categoryInfo;
}

/*! \brief Returns the count of applets present in the active category.
 *
 * Note that it is not very cheap, because it forces the items (widgets) to be
 * loaded. So only use it in case you want to load the items anyway
 */
int
DcpAppletCategoryPage::appletCount()
{
    // this forces loading the items
    if (!isContentCreated()) {
        createContent();
    } else if (m_LoadedAppletCategory != appletCategory()) {
        m_Category->setCategoryInfo (m_CategoryInfo);
    }

    return m_Category->metadataCount();
}

/*! \brief Returns the metadata at the specified position.
 *
 * Note, the same applies as for appletCount().
 */
DcpAppletMetadata*
DcpAppletCategoryPage::appletMetadata(int i)
{
    if (i < appletCount()) {
        return m_Category->appletMetadata(i);
    } else {
        return 0;
    }
}

/*!
 * If delayed is true, createContent creates an empty page that contains
 * the header label only. The body can be created later with createBody();
 *
 * The default behaviour is not delaying the creation of the body.
 */
void
DcpAppletCategoryPage::setDelayedContent(bool delayed)
{
    m_DelayedContent = delayed;
}

/*!
 * Create and show the body content of the page.
 */
void
DcpAppletCategoryPage::createBody()
{
    if (!m_Spacer) {
        // createContent did not run yet, so we can delay until it gets called:
        m_DelayedContent = false;
        return;
    }

    QGraphicsLinearLayout* layout = mainLayout();

    // Most Used Items:
    bool hasMostUsed = m_CategoryInfo->hasMostUsed();
    if (hasMostUsed) {
        m_MostUsed = new DcpMostUsed(this);
        m_MostUsed->hide ();
        connect (m_MostUsed, SIGNAL (itemsBecameAvailable()),
                 this, SLOT (mostUsedAppears()));
        if (m_MostUsed->itemsAvailable()) {
            mostUsedAppears();
        }
        connect (this, SIGNAL (appearing()), m_MostUsed, SLOT(refresh()));
    }

    // create the categories:
    QGraphicsWidget* categoryWidget = createCategories();

    // create the applet list:
    m_Category = new DcpAppletButtons(m_CategoryInfo, 0, 0);

    // add them to the layout:
    if (hasMostUsed) {
        // box around them:
        MContainer* container = new MContainer();
        container->setStyleName ("CommonContainerInverted");
        // TODO no retranslateUi is implemented for this -V
        //% "All settings"
        container->setTitle (qtTrId("qtn_sett_main_other"));
        layout->addItem(container);

        // put them in the box:
        QGraphicsLinearLayout* clayout =
            new QGraphicsLinearLayout (Qt::Vertical,
                                       container->centralWidget());
        addCategoryToLayoutOrdered (clayout, categoryWidget, m_Category);

    } else {
        // just add them to the layout without box:
        addCategoryToLayoutOrdered (layout, categoryWidget, m_Category);
    }

#ifdef PROGRESS_INDICATOR
    // show progress indicator while loading the applets:
    connect (m_Category, SIGNAL (loadingFinished()),
             this, SLOT (onLoadingFinished()));
    setProgressIndicatorVisible (true);
#endif
}

void
DcpAppletCategoryPage::retranslateUi()
{
    // briefwidgets take care of themselves, so we only update titles here
    setTitle(m_CategoryInfo ? m_CategoryInfo->title() : QString());
    if (isContentCreated()) {
        setTitleLabel (m_CategoryInfo->helpId());
    }
}

void
DcpAppletCategoryPage::onLoadingFinished ()
{
#ifdef PROGRESS_INDICATOR
    setProgressIndicatorVisible (false);
#endif
}


