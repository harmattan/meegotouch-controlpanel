/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 sts=4: */

#ifndef DCPAPPLETOBJECT_H
#define DCPAPPLETOBJECT_H

#include "dcpappletplugin.h" 
#include <QString>
class DcpAppletIf;
class DcpAppletMetadata;
class DcpBrief;
class DcpWidget;

class DcpAppletObjectPrivate;

class DcpAppletObject : public DcpAppletPlugin
{
    Q_OBJECT
public:
    DcpAppletObject(DcpAppletMetadata *metadata);
    virtual ~DcpAppletObject();

    QString toggleIconId () const;

    int widgetTypeID () const;

    Qt::Alignment align () const;
    bool toggle () const;

    QString text1 () const;
    QString text2 () const;
    QString imageName() const;
    int getMainWidgetId () const;

signals:
    void briefChanged ();
    void activate (int pageId);

public slots:
    void slotClicked ();
    void setToggle (bool checked);
    bool activatePluginByName (const QString &name) const;
    void activateSlot(int widgetId = -1);

protected:
    DcpBrief* brief() const;

private:
    DcpAppletObjectPrivate *const d_ptr;
    Q_DISABLE_COPY (DcpAppletObject);
};

#endif

