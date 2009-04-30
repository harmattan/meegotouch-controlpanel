#include "keyboarddialog.h"
#include "keyboardwidget.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include "dcplanguage.h"
#include "dcplanguageconf.h"
#include <duiquerydialog.h>

KeyboardDialog::KeyboardDialog()
              :DcpDialog()
{
    initWidget();
}

KeyboardDialog::~KeyboardDialog()
{
}

void KeyboardDialog::initWidget()
{
    m_OldLanguages = DcpLanguageConf::instance()->keyboardLanguages();
    KeyboardWidget *m_Widget = new KeyboardWidget(this);
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->addItemAtPosition(m_Widget, 0, Qt::AlignCenter);

    connect(DuiDeviceProfile::instance(), SIGNAL(orientationAngleChanged (DuiDeviceProfile::DeviceOrientationAngle)),
            this, SLOT(onOrientationAngleChanged ()));
    onOrientationAngleChanged();
    this->setLayout(mainLayout);
}


void KeyboardDialog::onOrientationAngleChanged ()
{
    QSizeF dialogSize = DuiDeviceProfile::instance()->resolution();
    dialogSize.setHeight(dialogSize.height()-60);
    layout()->itemAt(0)->setMinimumSize(dialogSize);
    layout()->itemAt(0)->setMaximumSize(dialogSize);
}

void KeyboardDialog::close()
{
    if (!DcpLanguageConf::instance()->keyboardLanguagesNumber()) {
            DuiQueryDialog query("You have not selected any keyboard language,<br>"
                                 "would you like to keep the previous selection?");
            query.setParent(this);
            DuiButton* keepPrevious = query.addButton("Keep previous");
            query.addButton("Select new");
            query.exec();
            if (query.clickedButton() != keepPrevious) //DuiDialog::Accepted is wrong!!!
            {
                qDebug("DCP: accepted");
                DcpLanguageConf::instance()->setKeyboardLanguages(m_OldLanguages);
                DcpDialog::close();
            }
    } else {
        DcpDialog::close();
    }
}

