#include "keyboarddialog.h"
#include "keyboardwidget.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include "dcplanguage.h"
#include "dcplanguageconf.h"
#include <DuiMessageBox>
        
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
            DuiMessageBox mb("Keep last selection of languages?",
                             DuiMessageBox::Ok|DuiMessageBox::Cancel);
            int result = mb.exec();
            qDebug() << "DCP: result is" << result;
            if (result == 1) //DuiDialog::Accepted is wrong!!!
            {
                qDebug("DCP: accepted");
               DcpLanguageConf::instance()->setKeyboardLanguages(m_OldLanguages);
              DcpDialog::close();
            }
            else
            {
              mb.disappear();  
              return; 
            }
        }
    DcpDialog::close();
}
