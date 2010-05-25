/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 sts=4: */
#ifndef DCPAPPLETPLUGIN_FAKE_H
#define DCPAPPLETPLUGIN_FAKE_H
#include "dcpappletplugin.h"
#include "dcpappletplugin_p.h"
//#include "dcpappletmetadata-fake.h"
#include "dcpappletmetadata.h"

DcpAppletPlugin::DcpAppletPlugin(DcpAppletMetadata *metadata)

    : d_ptr(new DcpAppletPluginPrivate(metadata))  
{};
#endif
