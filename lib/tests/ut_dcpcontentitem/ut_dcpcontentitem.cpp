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

#include "ut_dcpcontentitem.h"
#include "dcpcontentitem_p.h"
#include "mcontentitemmodel.h"

void Ut_DcpContentItem::initTestCase()
{
}

void Ut_DcpContentItem::cleanupTestCase()
{
}

void Ut_DcpContentItem::init()
{
    m_Target = new DcpContentItem();
}

void Ut_DcpContentItem::cleanup()
{
    delete m_Target;
}

void Ut_DcpContentItem::testConstructor()
{
    // verifies that the parent is set correctly
    QVERIFY (!m_Target->parentItem());
    DcpContentItem* child = new DcpContentItem(0, m_Target);
    QCOMPARE (child->parentItem(), m_Target);
}

void Ut_DcpContentItem::testSetApplet()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->setApplet (applet);

    // was the applet set?
    QCOMPARE (m_Target->d_ptr->m_Applet, applet);

    // were the signals connected?
    // ... TODO: briefChanged from the applet and clicked to the applet
}

void Ut_DcpContentItem::testMattiId()
{
    QString matti = "12345";
    m_Target->setMattiID(matti);
    QCOMPARE (m_Target->mattiID(), matti);
}

void Ut_DcpContentItem::testUpdateContents()
{
    
}

void Ut_DcpContentItem::testRetranslateUi()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->setApplet (applet);

    // test if updateText gets called on retranslateUi
    m_Target->setTitle ("xxx");
    m_Target->updateText();
    QCOMPARE (m_Target->title(), applet->text1());
}

void Ut_DcpContentItem::testShowHideEvent()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->setApplet (applet);

    // check if the widget updates on showEvent
    m_Target->setTitle ("xxx");
    m_Target->showEvent(0);
    QCOMPARE (m_Target->title(), applet->text1());

    // check if signals gets reconnected on showEvent
    // ... TODO
}

void Ut_DcpContentItem::testConstructRealWidget()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->d_ptr->m_Applet = applet;
    m_Target->constructRealWidget();

    // check if itemStyle is ok
    // TODO maybe we could check here with 2 plugins with different widgetTypeIDs
    QCOMPARE (m_Target->d_ptr->m_WidgetTypeId, (int)DcpWidgetType::Label);
    QCOMPARE (m_Target->model()->itemStyle(), (int)MContentItem::TwoTextLabels);
}

void Ut_DcpContentItem::testUpdateText()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->setApplet (applet);
    m_Target->setTitle ("xxx");

    m_Target->updateText();

    // updates the texts:
    QCOMPARE (m_Target->title(), QString("fake-text1"));
    QCOMPARE (m_Target->subtitle(), QString("fake-text2"));

    // changes the itemstyle into two line mode correctly:
    QCOMPARE ((int)m_Target->model()->itemStyle(),
              (int)MContentItem::TwoTextLabels);
}

void Ut_DcpContentItem::testUpdateImage()
{
    DcpAppletObject* applet =
        new DcpAppletObject(new DcpAppletMetadata("fake"));
    m_Target->setApplet (applet);
    m_Target->d_ptr->m_WidgetTypeId = DcpWidgetType::Image;

    m_Target->updateImage ();

    // updates the values:
    QCOMPARE (m_Target->d_ptr->m_ImageName, QString("fake-imageName"));
    // it should store the pointer, because of the image release from mtheme
    QVERIFY (m_Target->d_ptr->m_Pixmap);
}

void Ut_DcpContentItem::testSetImageFromFile()
{
    m_Target->setImage(QImage(10,10, QImage::Format_ARGB32));

    // it changes correctly to a null image (image could not be loaded)
    m_Target->setImageFromFile("fake");
    QCOMPARE (m_Target->image(), QImage());

    // TODO: a test with a succesful image maybe: needs a fake QFile?
}

void Ut_DcpContentItem::testSetImageName()
{
    m_Target->setImageName ("fake");
    // it should store the pointer, because of the image release from mtheme
    QVERIFY (m_Target->d_ptr->m_Pixmap);
}

void Ut_DcpContentItem::testReleaseImage()
{
    QVERIFY (!m_Target->d_ptr->m_Pixmap);
    m_Target->setImageName ("fake");
    QVERIFY (m_Target->d_ptr->m_Pixmap);
    m_Target->releaseImage ();
    QVERIFY (!m_Target->d_ptr->m_Pixmap);
}

void Ut_DcpContentItem::testInvertTwoLineMode()
{
    m_Target->model()->setItemStyle(MContentItem::IconAndTwoTextLabels);
    m_Target->invertTwoLineMode ();
    QCOMPARE ((int)m_Target->model()->itemStyle(),
              (int)MContentItem::IconAndSingleTextLabel);
    m_Target->invertTwoLineMode ();
    QCOMPARE ((int)m_Target->model()->itemStyle(),
              (int)MContentItem::IconAndTwoTextLabels);

    m_Target->model()->setItemStyle(
              MContentItem::SingleTextLabel);
    m_Target->invertTwoLineMode ();
    QCOMPARE ((int)m_Target->model()->itemStyle(),
              (int)MContentItem::TwoTextLabels);
    m_Target->invertTwoLineMode ();
    QCOMPARE ((int)m_Target->model()->itemStyle(),
              (int)MContentItem::SingleTextLabel);
}



QTEST_APPLESS_MAIN(Ut_DcpContentItem)

