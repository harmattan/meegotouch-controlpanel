#ifndef TESTAPPLETWIDGET_H__
#define TESTAPPLETWIDGET_H__

#include <DcpWidget>

class TestAppletWidget : public DcpWidget
{
   Q_OBJECT

    public:
       TestAppletWidget(QGraphicsWidget *parent=0);
       virtual ~TestAppletWidget();
};

#endif
