/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpmainpage.h"

#include <QtDebug>
#include <DuiApplication>

#include <DcpMainCategory>
#include <Pages>
#include <DcpApplet>
#include <QGraphicsLinearLayout>

#include "dcpdescriptioncomponent.h"
#include "dcpcategorycomponent.h"
#include "maintranslations.h"

#define DEBUG
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
	DcpPage(), m_RecentlyComp(0)
{
    setEscapeButtonMode (DuiEscapeButtonPanelModel::CloseMode);
}

DcpMainPage::~DcpMainPage()
{
}


void
DcpMainPage::createContent()
{
    DcpPage::createContent();

    QGraphicsLinearLayout* layout = mainLayout();

    // most recent used items:
    m_RecentlyComp = new DcpCategoryComponent(0,
                                 DcpApplet::MostUsedCategory,
                                 DcpMain::mostRecentUsedTitleId);

    layout->addItem(m_RecentlyComp);

    // category descriptions:
    for (int i = 0;; i++) {
        DcpCategoryComponent *component;

        DcpCategoryInfo info = DcpMain::CategoryInfos[i];
        if (info.titleId == 0)
             break;
#if 0
        component = new DcpCategoryComponent (
                0, info.appletCategory, info.titleId);
#else
        component = new DcpCategoryComponent (0, &info);
#endif

        layout->addItem(component);
    }

    setEscapeButtonMode (DuiEscapeButtonPanelModel::CloseMode);

    retranslateUi();
}

void DcpMainPage::retranslateUi()
{
    QGraphicsLinearLayout* layout = mainLayout();

    setTitle (qtTrId(DcpMain::settingsTitleId));
    m_RecentlyComp->setTitle (qtTrId(DcpMain::mostRecentUsedTitleId));

    for (int i = layout->count() - 1; i >= 1; i--) {
        DcpCategoryComponent* comp =
            dynamic_cast<DcpCategoryComponent*> (layout->itemAt(i));

        comp->setTitle (qtTrId(DcpMain::CategoryInfos[i - 1].titleId));
    }
    // no need to update briefs, they take care of themselves
}

void
DcpMainPage::organizeContent (
        const Dui::Orientation& ori)
{
    QGraphicsLayout* layout = mainLayout();

    for (int i = layout->count() - 1; i >= 0; i--) {
        DcpCategoryComponent* comp =
            dynamic_cast<DcpCategoryComponent*>(layout->itemAt(i));

        comp->onOrientationChange (ori);
    }

    DcpPage::organizeContent(ori);
}

void DcpMainPage::reload()
{
    // refresh the most recent items sequence:
    if (m_RecentlyComp){
        m_RecentlyComp->reload();
    }

    // DcpBriefWidget takes care of all the other things
    DcpPage::reload();
}

// if clicked fast, back button can be pressed instead of close
void DcpMainPage::back()
{
    qApp->quit();
}

