#include "displaydialog.h"
#include "displaywidget.h"
#include "languageselectcontainer.h"

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
    DisplayWidget *widget = new DisplayWidget();

    DuiLayout *mainLayout = new DuiLayout();
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->addItemAtPosition(widget, 0, Qt::AlignCenter);
    setLayout(mainLayout);
    connect(widget, SIGNAL(clicked()), this, SLOT(accept()));

    // TODO onOrientationChange
    QSizeF dialogSize = DuiDeviceProfile::instance()->resolution();
    dialogSize.setHeight(dialogSize.height()-60);
    this->setContentsMargins(15,0,15,0);
    this->setMinimumSize(dialogSize);
}

