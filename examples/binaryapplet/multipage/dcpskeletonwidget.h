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

#ifndef SKELETONWIDGET_H
#define SKELETONWIDGET_H

#include <DcpStylableWidget>

class MLabel;
class MButton;

class SkeletonWidget : public DcpStylableWidget
{
    Q_OBJECT

public:
    SkeletonWidget(int num, QGraphicsWidget *parent = 0);
    virtual ~SkeletonWidget();

    virtual bool back ();

protected slots:
    void onPageOpenRequest ();

private:
    MButton* createButton (const QString& title, const char* method);
    MButton* m_PreventQuitToggle;
};

#endif // SKELETONWIDGET_H

