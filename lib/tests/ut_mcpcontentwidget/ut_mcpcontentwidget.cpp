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

#include "ut_mcpcontentwidget.h"
#include "mcpcontentwidget_p.h"
#include "mcontentitemmodel.h"

#include <MImageWidget>
#include <QPixmap>

void Ut_McpContentWidget::initTestCase()
{
}

void Ut_McpContentWidget::cleanupTestCase()
{
}

void Ut_McpContentWidget::init()
{
    m_Target = new McpContentWidget();
}

void Ut_McpContentWidget::cleanup()
{
    delete m_Target;
}

void Ut_McpContentWidget::testConstructor()
{
    // verifies that the parent is set correctly
    QVERIFY (!m_Target->parentItem());
    McpContentWidget* child = new McpContentWidget(0, m_Target);
    QCOMPARE (child->parentItem(), m_Target);
    delete child;
}

void Ut_McpContentWidget::testSetApplet()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->setApplet (applet);

    // was the applet set?
    QCOMPARE (m_Target->d_ptr->m_Applet, applet);

    // were the signals connected?
    // ... TODO: briefChanged from the applet and clicked to the applet
}

void Ut_McpContentWidget::testMattiId()
{
    QString matti = "12345";
    m_Target->setMattiID(matti);
    QCOMPARE (m_Target->mattiID(), matti);
}

void Ut_McpContentWidget::testUpdateContents()
{
    QSKIP ("Not implemented", SkipAll);
}

void Ut_McpContentWidget::testRetranslateUi()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->setApplet (applet);

    // test if updateText gets called on retranslateUi
    m_Target->d_ptr->m_Text1W->setText ("xxx");
    m_Target->retranslateUi();
    QCOMPARE (m_Target->d_ptr->m_Text1W->text(), applet->text1());
}

void Ut_McpContentWidget::testShowHideEvent()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->setApplet (applet);
    m_Target->hideEvent(0);

    // check if the widget updates on showEvent
    m_Target->d_ptr->m_Text1W->setText ("xxx");
    m_Target->showEvent(0);
    QCOMPARE (m_Target->d_ptr->m_Text1W->text(), applet->text1());

    // check if signals gets reconnected on showEvent
    // ... TODO
}

void Ut_McpContentWidget::testConstructRealWidget()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->d_ptr->m_Applet = applet;
    m_Target->constructRealWidget();

    // TODO implement checks
    QCOMPARE (m_Target->widgetType(), (int)DcpWidgetType::Label);
}

void Ut_McpContentWidget::testUpdateText()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->setApplet (applet);
    m_Target->d_ptr->m_Text1W->setText ("xxx");

    m_Target->updateText();

    // updates the texts:
    QCOMPARE (m_Target->title(), QString("fake-text1"));
    QCOMPARE (m_Target->subtitle(), QString("fake-text2"));
    QCOMPARE (m_Target->d_ptr->m_Text1W->text(), QString("fake-text1"));
    QCOMPARE (m_Target->d_ptr->m_Text2W->text(), QString("fake-text2"));


    // changes the itemstyle into two line mode correctly:
    QVERIFY (m_Target->hasTwoTextLines());
}

void Ut_McpContentWidget::testUpdateImage()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->setApplet (applet);

    // does not update if the type is not image:
    m_Target->updateImage ();


    QSKIP ("Not implemented", SkipAll);

    // QCOMPARE (m_Target->imageID(), QString("fake-imageName"));
    // TODO check that it calls the appropriate image setters
}


void Ut_McpContentWidget::testSetImageFromFile()
{
    m_Target->d_ptr->m_ImageW = new MImageWidget();

    // it changes correctly to a null image (image could not be loaded)
    m_Target->setImageFromFile("image");
    QCOMPARE (m_Target->d_ptr->m_ImageW->image(), QString("image"));

    // TODO: a test with a succesful image maybe: needs a fake QFile?
}

void Ut_McpContentWidget::testSetImageName()
{
    m_Target->d_ptr->m_ImageW = new MImageWidget();
    m_Target->setImageName ("fake");
    QCOMPARE (m_Target->d_ptr->m_ImageW->image(), QString("fake"));
}

void Ut_McpContentWidget::testWidgetType()
{
    QSKIP ("Not implemented.", SkipAll);
}

void Ut_McpContentWidget::testHasTwoTextLines()
{
    QSKIP ("Not implemented.", SkipAll);
}

void Ut_McpContentWidget::testIsChecked()
{
    QSKIP ("Not implemented.", SkipAll);
}

void Ut_McpContentWidget::testTextGetters()
{
    QSKIP ("Not implemented.", SkipAll);
}

void Ut_McpContentWidget::testEnsureLayoutIsCreated()
{
    QSKIP ("Not implemented.", SkipAll);
}

void Ut_McpContentWidget::testEnsureImageIsCreated()
{
    QSKIP ("Not implemented.", SkipAll);
}

void Ut_McpContentWidget::testEnsureToggleIsCreated()
{
    QSKIP ("Not implemented.", SkipAll);
}

void Ut_McpContentWidget::testEnsureTextsAreCreated()
{
    QSKIP ("Not implemented.", SkipAll);
}

void Ut_McpContentWidget::testEnsureWidgetsAreLayouted()
{
    QSKIP ("Not implemented.", SkipAll);
}


QTEST_APPLESS_MAIN(Ut_McpContentWidget)


