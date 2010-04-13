#include <DuiLabel>
#include <DuiContainer>
#include <DuiLayout>
#include <DuiLinearLayoutPolicy>
#include <DuiButton>
#include <DuiButtonGroup>
#include "testappletwidget.h"

TestAppletWidget::TestAppletWidget(QGraphicsWidget *parent)
    : DcpWidget(parent)
{
    DuiLayout *layout = new DuiLayout(this);
    DuiLinearLayoutPolicy *layoutPolicy = 
        new DuiLinearLayoutPolicy(layout, Qt::Vertical);
    layout->setPolicy(layoutPolicy);

    DuiLabel *widget = new DuiLabel("Test applet1", this);
    layoutPolicy->addItem(widget, Qt::AlignLeft);

    /*
    DuiContainer *container = new DuiContainer("Test container", this);
    layoutPolicy->addItem(container);

    DuiButtonGroup *buttongrp = new DuiButtonGroup();
    for (int i = 0; i < 3; ++i) {
        DuiButton *button = new DuiButton(QString("%1").arg(i));
        buttongrp->addButton(button);
        layoutPolicy->addItem(button);
    }
*/
    setLayout(layout);

}

TestAppletWidget::~TestAppletWidget()
{
}
