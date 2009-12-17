/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 sts=4: */

#include "dcpbrief.h"
#include "dcpwidgettypes.h"

#define DEBUG
#include "../../../lib/src/dcpdebug.h"

DcpBrief::~DcpBrief()
{
}

/*!
 *
 * Default implementation of the widgetTypeID() virtual function. This function
 * should return an invalid value so that we know that we should search the
 * desktop file for a textual representation of the required widget type.
 */
int
DcpBrief::widgetTypeID () const
{
    return DCPBRIEFWIDGETINVALID;
}

QString DcpBrief::icon() const
{
    return QString();
}

QString DcpBrief::toggleIconId() const
{
    return QString();
}

QString DcpBrief::valueText() const
{
    return QString();
}

Qt::Alignment DcpBrief::align() const
{
    return Qt::AlignLeft;
}

bool 
DcpBrief::toggle() const
{
    return false;
}

QString DcpBrief::image() const
{
    return QString();
}

void DcpBrief::setToggle (bool) 
{
}

