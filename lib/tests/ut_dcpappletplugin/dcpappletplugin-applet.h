/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#ifndef DCPAPPLETLOADER_APPLET_H__
#define DCPAPPLETLOADER_APPLET_H__

#include <QObject>
#include <QVector>
#include <MAction>
#include <QtDebug>

#include "dcpappletif.h"

class DcpAppletPluginApplet : public QObject, public DcpAppletIf {
    Q_OBJECT
    Q_INTERFACES(DcpAppletIf)

    public:
        DcpAppletPluginApplet() : m_Initialized(false) {
        }
        virtual void init() { 
            m_Initialized = true;
        }
        virtual DcpWidget *constructWidget(int) {return 0;};
        virtual QString title() const { return 0; };
        virtual QVector<MAction *> viewMenuItems() {
            QVector<MAction*> empty;
            return empty;
        }
        virtual DcpBrief* constructBrief(int) { return 0; };

        bool initialized() {
            return m_Initialized;
        }

    private:
        bool m_Initialized;
};

#endif
