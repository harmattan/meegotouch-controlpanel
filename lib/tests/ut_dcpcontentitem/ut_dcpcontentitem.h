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
    void testMattiId();
    void testUpdateContents();
    void testRetranslateUi();
    void testShowHideEvent();
    void testConstructRealWidget();
    void testUpdateText();
    void testUpdateImage();
    void testSetImageFromFile();
    void testSetImageName();
    void testReleaseImage();
    void testInvertTwoLineMode();

private:
    DcpContentItem* m_Target;

};

#endif // UT_DCPCONTENTITEM_H

