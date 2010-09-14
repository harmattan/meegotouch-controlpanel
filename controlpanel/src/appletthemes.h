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

#ifndef APPLETTHEMES_H
#define APPLETTHEMES_H

#include <QObject>
#include <QSet>
#include <QString>

class AppletThemes: public QObject
{
    Q_OBJECT

public:
    ~AppletThemes();
    static AppletThemes* instance();
    void ensureCssLoaded (const QString& appletName);

protected slots:
    void onThemeIsChanging();

protected:
    AppletThemes();

    QSet<QString> m_LoadedThemes;
    static AppletThemes* sm_Instance;

    friend class Ut_AppletThemes;
};


#endif // APPLETTHEMES_H
