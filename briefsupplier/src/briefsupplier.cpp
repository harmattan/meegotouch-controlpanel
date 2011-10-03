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

#include "briefsupplier.h"

#include <QtDebug>
#include <QCoreApplication>
#include <QLocalSocket>
#include <QLibrary>

#include <dcpappletdb.h>
#include <dcpappletobject.h>
#include <dcpbrief.h>
#include <dcpwidgettypes.h>
#include <dcpappletmetadata.h>
#include <dcpretranslator.h>
#include <dcpdebug.h>

#include "bsuppliercommands.h"
#include "stream.h"

#include <syslog.h>

using namespace BSupplier;

#define returnIf(test, st, param)  \
    if (test) { syslog(LOG_WARNING, st ": \"%s\"",qPrintable(param)); return; }

BriefSupplier::BriefSupplier(const QString &desktopDir):
    m_Stream (new Stream(this))
{
    // this makes loading a bit longer, but protects controlpanel from crash
    // in case the plugin has an unresolved symbol which situation cant be
    // avoided during SSU upgrades
    DcpAppletPlugin::setDefaultLoadHints (QLibrary::ResolveAllSymbolsHint);

    // init the stream:
    connect (m_Stream, SIGNAL (newCommand(QString)),
             this, SLOT (onCommandArrival(QString)));

    // connect to controlpanel
    QLocalSocket* socket = new QLocalSocket (this);
    connect (socket, SIGNAL (error (QLocalSocket::LocalSocketError)),
             this, SLOT (onConnectionDisconnected ()));
    connect (socket, SIGNAL (disconnected ()),
             this, SLOT (onConnectionDisconnected ()));
    setIODevice (socket);
    socket->connectToServer (BSupplier::BServerId);

    // init the db:
    DcpAppletDb *db = desktopDir.isEmpty() ? DcpAppletDb::instance() :
        DcpAppletDb::instance(desktopDir);
    DcpAppletMetadataList list = db->list ();

    // load all applet translations:
    DcpRetranslator::instance()->ensureTranslationsAreLoaded(list);
}

BriefSupplier::~BriefSupplier()
{
}


void BriefSupplier::onConnectionDisconnected()
{
    qApp->exit(0);
}

void BriefSupplier::onCommandArrival (const QString& command)
{
    if (command.startsWith(CmdWatch)) {
        watch (command.mid (CmdWatch.count()));
    } else if (command.startsWith(CmdUnwatch)) {
        unwatch (command.mid (CmdUnwatch.count()));
    } else if (command.startsWith(CmdSetValue)) {
        setValue (command.mid (CmdSetValue.count()));
    } else {
        qWarning ("Brief supplier: could not understand %s",
                  qPrintable (command));
    }
}

void BriefSupplier::watch (const QString& appletName)
{
    returnIf (appletName.isEmpty(), "Empty appletname", appletName);
    qDebug () << "Watching:" << appletName;

    DcpAppletObject* applet = DcpAppletDb::instance ()->applet (appletName);
    returnIf (!applet, "No such applet", appletName);

    DcpBrief* brief = applet->brief();
    if (brief) {
        connect (applet, SIGNAL (briefChanged()),
                this, SLOT (onBriefChanged()));
        DcpAppletMetadata* metadata = applet->metadata();
        if (metadata) {
            metadata->markActive();
            DcpRetranslator::instance()->ensureTranslationLoaded(metadata);
        }
        outputBrief (applet);
    }
}

void BriefSupplier::unwatch (const QString& appletName)
{
    returnIf (appletName.isEmpty(), "No appletName was specified", appletName);
    qDebug () << "Watching:" << appletName;

    DcpAppletObject* applet = DcpAppletDb::instance ()->applet (appletName);
    returnIf (!applet, "No such applet", appletName);
    DcpBrief* brief = applet->brief();
    if (!brief) return;

    // make it inactive
    disconnect (applet, SIGNAL (briefChanged()),
                this, SLOT (onBriefChanged()));

    DcpAppletMetadata* metadata = applet->metadata();
    if (metadata) {
        metadata->markInactive();
    }
}

void BriefSupplier::onBriefChanged ()
{
    DcpAppletObject* applet = qobject_cast<DcpAppletObject*>(sender());
    returnIf (!applet, "Strange error in onBriefChanged()", QString());

    outputBrief (applet);
}

void BriefSupplier::outputBrief (DcpAppletObject* applet, bool textOnly)
{
    dcp_failfunc_unless (applet);

    DcpBrief* brief = applet->brief();
    if (!brief) return;

    DcpAppletMetadata* metadata = applet->metadata();

    // get the values from the applet:
    QString appletName = metadata ? metadata->name() : QString();
    // the applet name is the id we use:
    returnIf (appletName.isEmpty(), "Applet without name", appletName);

    QString titleText = brief->titleText();
    QString valueText = brief->valueText();
    int widgetTypeID = -1;
    QString helpId;
    QString icon;
    QString image;
    QVariant value;
    int minValue = 0;
    int maxValue = 0;
    int sliderSteps = 0;

    if (!textOnly) {
        widgetTypeID = brief->widgetTypeID();
        helpId = applet->briefVersion() < 5 ? QString() : brief->helpId();

        switch (widgetTypeID) {
            case DcpWidgetType::Toggle:
            case DcpWidgetType::Button:
                value = brief->value();
                break;
            case DcpWidgetType::Image:
                icon = brief->icon();
                image = brief->image();
                break;
            case DcpWidgetType::Slider:
                minValue = brief->minValue();
                maxValue = brief->maxValue();
                sliderSteps = brief->sliderSteps();
                value = brief->value();
            case DcpWidgetType::ComboBox:
                value = brief->value();
            default:
                break;
        }
    }

    // send them:
    outputStart();
    output (OutputName, appletName);
    output (OutputTitleText, titleText);
    output (OutputValueText, valueText, true);
    if (widgetTypeID == DcpWidgetType::ComboBox) {
        QVariantList list = brief->possibleValues();
        QString listStr;
        listStr.reserve (128);
        foreach (QVariant value, list) {
            listStr += value.toString() + BSupplier::ParamSeparator;
        }
        if (listStr.endsWith (BSupplier::ParamSeparator)) {
            listStr.chop(1);
        }
        output (OutputPossibleValues, listStr);
    }

    if (!textOnly) {
        output (OutputWidgetTypeID, widgetTypeID);
        output (OutputIcon, image.isEmpty() ? icon : image);
        if (widgetTypeID == DcpWidgetType::Toggle ||
            widgetTypeID == DcpWidgetType::Button ||
            widgetTypeID == DcpWidgetType::Slider ||
            widgetTypeID == DcpWidgetType::ComboBox)
        {
            output (OutputValue, value.toString(), true);
        }
        if (widgetTypeID == DcpWidgetType::Slider) {
            // TODO we could minimize the traffic by remembering the last sent
            // values and only output them if they have changed
            if (minValue != 0) output (OutputMinValue, minValue);
            if (maxValue != 100) output (OutputMaxValue, maxValue);
            if (sliderSteps != 0) output (OutputValueStep, sliderSteps);
            output (OutputValue, value.toString(), true);
        }
        output (OutputHelpId, helpId);
    }

    outputEnd();
}

void BriefSupplier::setValue (const QString& params)
{
    // parse the params:
    QStringList paramList = params.split (BSupplier::ParamSeparator);
    returnIf (paramList.count() != 2, "Wrong parameters for setValue", params);
    const QString& appletName = paramList.at(0);
    const QString& newValue = paramList.at(1);

    // get the applet:
    returnIf (appletName.isEmpty(), "No appletName was specified", appletName);
    DcpAppletObject* applet = DcpAppletDb::instance ()->applet (appletName);
    returnIf (!applet, "No such applet", appletName);

    // set the new value:
    applet->setValue (newValue);
}

void BriefSupplier::onLocaleChange ()
{
    DcpAppletDb* db = DcpAppletDb::instance();
    DcpAppletMetadataList metadataList = db->list ();
    foreach (DcpAppletMetadata* metadata, metadataList) {
        if (metadata->isActive ()) {
            DcpAppletObject* applet = db->applet (metadata->name());
            outputBrief (applet, true);
        }
    }
}

void BriefSupplier::outputStart ()
{
    m_Stream->writeLine (OutputBegin);
}

void BriefSupplier::outputEnd ()
{
    m_Stream->writeLine (OutputEnd);
    m_Stream->flush ();
}

void BriefSupplier::output (const char* key, const QString& value, bool forced)
{
    if (forced || !value.isEmpty ()) {
        // the key and value is separated by the first "="
        m_Stream->writeLine (QString(key) + "=" + value);
    }
}

void BriefSupplier::output (const char* key, int value)
{
    output (key, QString::number (value));
}

void BriefSupplier::setIODevice (QIODevice* device)
{
    m_Stream->setIODevice (device);
}

