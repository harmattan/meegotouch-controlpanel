#include <MLabel>
#include <MContainer>
#include <MLayout>
#include <MLinearLayoutPolicy>
#include <MButton>
#include <MButtonGroup>
#include "testappletwidget2.h"

TestAppletWidget2::TestAppletWidget2(QGraphicsWidget *parent)
    : DcpWidget(parent)
{
    MLayout *layout = new MLayout(this);
    MLinearLayoutPolicy *layoutPolicy = 
        new MLinearLayoutPolicy(layout, Qt::Vertical);
    layout->setPolicy(layoutPolicy);

    MLabel *widget = new MLabel("Test applet2", this);
    layoutPolicy->addItem(widget, Qt::AlignLeft);

    setLayout(layout);

}

TestAppletWidget2::~TestAppletWidget2()
{
}
