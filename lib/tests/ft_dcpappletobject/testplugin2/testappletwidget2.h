#ifndef TESTAPPLETWIDGET2_H__
#define TESTAPPLETWIDGET2_H__

#include <DcpWidget>

class TestAppletWidget2 : public DcpWidget
{
   Q_OBJECT

    public:
       TestAppletWidget2(QGraphicsWidget *parent=0);
       virtual ~TestAppletWidget2();
};

#endif
