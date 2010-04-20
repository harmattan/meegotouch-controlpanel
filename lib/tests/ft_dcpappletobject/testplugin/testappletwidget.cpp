#include <MLabel>
#include <MContainer>
#include <MLayout>
#include <MLinearLayoutPolicy>
#include <MButton>
#include <MButtonGroup>
#include "testappletwidget.h"

TestAppletWidget::TestAppletWidget(QGraphicsWidget *parent)
    : DcpWidget(parent)
{
    MLayout *layout = new MLayout(this);
    MLinearLayoutPolicy *layoutPolicy = 
        new MLinearLayoutPolicy(layout, Qt::Vertical);
    layout->setPolicy(layoutPolicy);

    MLabel *widget = new MLabel("Test applet1", this);
    layoutPolicy->addItem(widget, Qt::AlignLeft);

    /*
    MContainer *container = new MContainer("Test container", this);
    layoutPolicy->addItem(container);

    MButtonGroup *buttongrp = new MButtonGroup();
    for (int i = 0; i < 3; ++i) {
        MButton *button = new MButton(QString("%1").arg(i));
        buttongrp->addButton(button);
        layoutPolicy->addItem(button);
    }
*/
    setLayout(layout);

}

TestAppletWidget::~TestAppletWidget()
{
}
