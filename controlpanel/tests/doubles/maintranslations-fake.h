/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef MAINTRANSLATIONS_FAKE_H
#define MAINTRANSLATIONS_FAKE_H

#include "maintranslations.h"

/*
 * The applet categories that will be shown in the main window of the control
 * panel.
 */
const DcpCategoryInfo fakeInfo = 
    {
        //% "Look & Feel"
        QT_TRID_NOOP ("qtn_sett_main_look"),
        "Fake Look & Feel",
        PageHandle::LOOKANDFEEL,
        0 
    };

const char* DcpMain::settingsTitleId = QT_TRID_NOOP("qtn_sett_main_title");
const char* DcpMain::mostRecentUsedTitleId = QT_TRID_NOOP("qtn_sett_main_most");
const char* DcpMain::otherCategoriesTitleId = QT_TRID_NOOP("qtn_sett_main_other");
const char* DcpMain::quitMenuItemTextId = QT_TRID_NOOP("qtn_comm_exit");

const DcpCategoryInfo *
dcp_find_category_info (
        PageHandle::PageTypeId   id,
        const DcpCategoryInfo   *info)
{
    Q_UNUSED(id);
    Q_UNUSED(info);
    return &fakeInfo;
}

const DcpCategoryInfo *
dcp_find_category_info (
        const QString           &name,
        const DcpCategoryInfo   *info)
{
    Q_UNUSED(name);
    Q_UNUSED(info);
    return &fakeInfo;
}

bool
dcp_category_name_enlisted (
        const QString           &name)
{
    Q_UNUSED(name);
    return true;
}
#endif // MAINTRANSLATIONS_FAKE_H
