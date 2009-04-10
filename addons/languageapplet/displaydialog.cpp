#include "displaydialog.h"
#include "displaywidget.h"
#include "dcpspaceritem.h"
#include "languageselectcontainer.h"

#include <duitheme.h>
#include <duilabel.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include "dcplanguage.h"

DisplayDialog::DisplayDialog()
              :DuiDialog()
{
    initWidget();
}

DisplayDialog::~DisplayDialog()
{
}
void DisplayDialog::initWidget()
{
    DisplayWidget *widget = new DisplayWidget(this);
    DuiLayout *mainLayout = new DuiLayout(this);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(2.0, 10.0, 2.0, 10.0);
    mainLayoutPolicy->addItemAtPosition(widget, 1, Qt::AlignCenter);
}

