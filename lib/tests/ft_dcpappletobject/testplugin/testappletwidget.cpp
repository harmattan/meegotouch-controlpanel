#include <DuiLabel>
#include <DuiLayout>
#include <DuiLinearLayoutPolicy>
#include "testappletwidget.h"

TestAppletWidget::TestAppletWidget(QGraphicsWidget *parent)
    : DcpWidget(parent)
{
    DuiLayout *layout = new DuiLayout(this);
    DuiLinearLayoutPolicy *layoutPolicy = 
        new DuiLinearLayoutPolicy(layout, Qt::Horizontal);
    layout->setPolicy(layoutPolicy);

    DuiLabel *label = new DuiLabel("Test applet", this);
    layoutPolicy->addItem(label, Qt::AlignLeft);
    setLayout(layout);
}

TestAppletWidget::~TestAppletWidget()
{
}
