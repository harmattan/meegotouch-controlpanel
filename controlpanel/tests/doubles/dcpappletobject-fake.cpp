/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPAPPLETOBJECT_FAKE
#define DCPAPPLETOBJECT_FAKE
#include "dcpappletobject.h"
#include "dcpappletobject_p.h"
#include "dcpappletmetadata.h"
#include "dcpappletplugin-fake.h"
#include "dcpwidgettypes.h"

DcpAppletObject::DcpAppletObject(DcpAppletMetadata *metadata): DcpAppletPlugin(metadata),
 d_ptr(new DcpAppletObjectPrivate())
{
};
int 
DcpAppletObject::widgetTypeID () const
{
    return DcpWidgetType::Label;
}

Qt::Alignment 
DcpAppletObject::align () const
{
    return Qt::AlignLeft;
}

bool 
DcpAppletObject::toggle () const
{
    return false;
}

QString
DcpAppletObject::text1 () const
{
    return metadata()->text1();
}

QString 
DcpAppletObject::text2 () const
{
    return metadata()->text2();
}
 
QString 
DcpAppletObject::imageName() const
{
    return  metadata()->imageName();
}

QString 
DcpAppletObject::toggleIconId () const
{
    return metadata()->toggleIconId();
}



bool 
DcpAppletObject::activatePluginByName (
        const QString &appletName) const
{
    Q_UNUSED(appletName);
    return false;
}

void 
DcpAppletObject::setToggle(bool checked)
{
    Q_UNUSED(checked);
}

int 
DcpAppletObject::getMainWidgetId () const
{
    return -1;//applet()->partID(metadata()->part());
}

DcpBrief *
DcpAppletObject::brief () const
{
    return 0;
}


void 
DcpAppletObject::slotClicked ()
{
    metadata()->incrementUsage();
    activateSlot();
}

void
DcpAppletObject::activateSlot (int pageId)
{
    emit activate(pageId);
}
#endif
