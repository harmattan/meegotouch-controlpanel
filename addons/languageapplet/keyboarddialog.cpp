#include "keyboarddialog.h"
#include "keyboardwidget.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include "dcplanguage.h"
        
KeyboardDialog::KeyboardDialog()
              :DuiDialog()
{
    initWidget();
}

KeyboardDialog::~KeyboardDialog()
{
}

void KeyboardDialog::initWidget()
{
    KeyboardWidget *widget = new KeyboardWidget();

    DuiLayout *mainLayout = new DuiLayout();
    mainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->addItemAtPosition(widget, 0, Qt::AlignCenter);
    setLayout(mainLayout);
    connect(DuiDeviceProfile::instance(), SIGNAL(orientationAngleChanged (DuiDeviceProfile::DeviceOrientationAngle)),
            this, SLOT(onOrientationAngleChanged ()));
    onOrientationAngleChanged();
}


void KeyboardDialog::onOrientationAngleChanged ()
{
    QSizeF dialogSize = DuiDeviceProfile::instance()->resolution();
    dialogSize.setHeight(dialogSize.height()-60);
    this->setMinimumSize(dialogSize);
    this->setMaximumSize(dialogSize);
}
