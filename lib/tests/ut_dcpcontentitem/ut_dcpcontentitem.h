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

#ifndef UT_DCPCONTENTITEM_H
#define UT_DCPCONTENTITEM_H

#include <QtTest/QtTest>
#include <QObject>

#include <dcpcontentitem.h>

class Ut_DcpContentItem : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testConstructor();
    void testSetApplet();
    void testTDriverID();
    void testUpdateContents();
    void testRetranslateUi();
    void testConstructRealWidget();
    void testUpdateText();
    void testUpdateImage();
    void testSetImageFromFile();
    void testSetImageName();

    void testWidgetType();
    void testHasTwoTextLines();
    void testIsChecked();
    void testTextGetters();
    void testEnsureLayoutIsCreated();
    void testEnsureImageIsCreated();
    void testEnsureSliderIsCreated();
    void testEnsureToggleIsCreated();
    void testEnsureTextsAreCreated();
    void testEnsureWidgetsAreLayouted();
    void testUseless();

private:
    DcpContentItem* m_Target;

};

#endif // UT_DCPCONTENTITEM_H


