#include "displaydialog.h"
#include "displaywidget.h"
#include "languageselectcontainer.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include "dcplanguage.h"

DisplayDialog::DisplayDialog()
              :DcpDialog()
{
    initWidget();
}

DisplayDialog::~DisplayDialog()
{
}

void DisplayDialog::initWidget()
{
    setObjectName("DcpDialog");
    DisplayWidget *widget = new DisplayWidget(this);
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->addItemAtPosition(widget, 0, Qt::AlignCenter);   
    connect(widget, SIGNAL(clicked()), this, SLOT(accept()));
    connect(DuiDeviceProfile::instance(), 
            SIGNAL(orientationAngleChanged (DuiDeviceProfile::DeviceOrientationAngle)),
            this, SLOT(onOrientationAngleChanged ()));
    onOrientationAngleChanged();
    this->setLayout(mainLayout);
}

void DisplayDialog::onOrientationAngleChanged ()
{
    QSizeF dialogSize = DuiDeviceProfile::instance()->resolution();
    dialogSize.setHeight(dialogSize.height()-60);
    layout()->itemAt(0)->setMinimumSize(dialogSize);
    layout()->itemAt(0)->setMaximumSize(dialogSize);
}
