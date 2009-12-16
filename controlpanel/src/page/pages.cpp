/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#define DEBUG
#include "../../../lib/src/dcpdebug.h"

#include "pages.h"

PageHandle::PageHandle (
        PageTypeId      pageType, 
        const QString  &name,
        int             widgetId):
    id (pageType),
    param (name),
    m_widgetId (widgetId)
{
}


QString
PageHandle::getStringVariant ()
{
    return param + "://" + id + "/" + m_widgetId;
}
