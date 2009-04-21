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
    setObjectName("DcpDialog");
    DisplayWidget *widget = new DisplayWidget();

    DuiLayout *mainLayout = new DuiLayout();
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->addItemAtPosition(widget, 0, Qt::AlignCenter);
    setLayout(mainLayout);
    connect(widget, SIGNAL(clicked()), this, SLOT(accept()));
    connect(DuiDeviceProfile::instance(), SIGNAL(orientationAngleChanged (DuiDeviceProfile::DeviceOrientationAngle)),
            this, SLOT(onOrientationAngleChanged ()));
    onOrientationAngleChanged();
}


void DisplayDialog::onOrientationAngleChanged ()
{
    QSizeF dialogSize = DuiDeviceProfile::instance()->resolution();
    dialogSize.setHeight(dialogSize.height()-60);
    this->setMinimumSize(dialogSize);
    this->setMaximumSize(dialogSize);
}

