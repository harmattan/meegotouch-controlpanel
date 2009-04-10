#include "displaydialog.h"
#include "displaywidget.h"
#include "dcpspaceritem.h"
#include "languageselectcontainer.h"

#include <duitheme.h>
#include <duilabel.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duipannableviewport.h>
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
    DuiPannableViewport* viewport = new DuiPannableViewport(this);
    DisplayWidget *widget = new DisplayWidget();
    viewport->setWidget(widget);
    viewport->setObjectName("LanguageViewport");
    DuiLayout *mainLayout = new DuiLayout();
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->addItemAtPosition(viewport, 0, Qt::AlignCenter);
    setLayout(mainLayout);
    connect(widget, SIGNAL(clicked()), this, SLOT(accept()));
}

