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
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->addItemAtPosition(widget, 0, Qt::AlignCenter);
    setLayout(mainLayout);
    connect(widget, SIGNAL(clicked()), this, SLOT(accept()));

    // TODO onOrientationChange
    QSizeF dialogSize = DuiDeviceProfile::instance()->resolution();
    dialogSize.setHeight(dialogSize.height()-60);
    this->setContentsMargins(15,20,15,20);
    this->setMinimumSize(dialogSize);
}
