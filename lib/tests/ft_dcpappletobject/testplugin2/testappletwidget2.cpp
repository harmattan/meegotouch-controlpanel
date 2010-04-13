#include <DuiLabel>
#include <DuiContainer>
#include <DuiLayout>
#include <DuiLinearLayoutPolicy>
#include <DuiButton>
#include <DuiButtonGroup>
#include "testappletwidget2.h"

TestAppletWidget2::TestAppletWidget2(QGraphicsWidget *parent)
    : DcpWidget(parent)
{
    DuiLayout *layout = new DuiLayout(this);
    DuiLinearLayoutPolicy *layoutPolicy = 
        new DuiLinearLayoutPolicy(layout, Qt::Vertical);
    layout->setPolicy(layoutPolicy);

    DuiLabel *widget = new DuiLabel("Test applet2", this);
    layoutPolicy->addItem(widget, Qt::AlignLeft);

    setLayout(layout);

}

TestAppletWidget2::~TestAppletWidget2()
{
}
