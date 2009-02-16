#include <QtDebug>
#include <duipannableviewport.h>

<<<<<<< HEAD:src/component/page/duisettingspage.cpp
#include <duibutton.h>

#include <QGridLayout>

#include "duisimplecategory.h"
#include "duimaincategory.h"
=======
#include "duisettingspage.h"

>>>>>>> 011a46d6151cf9c3f6f525ddff7d47fd85a0c355:src/component/page/duisettingspage.cpp

#include "button2.h"

DuiSettingsPage::DuiSettingsPage()
{
}


void DuiSettingsPage::createContent()
{
<<<<<<< HEAD:src/component/page/duisettingspage.cpp
    DuiLinearLayout* mainLayout = new DuiLinearLayout(Qt::Vertical);

    DuiLabel* title = new DuiLabel("Title");
    title->setAlignment(Qt::AlignCenter);
    title->setMaximumHeight(130);

    title->setMinimumWidth(300);

    mainLayout->addItem(title);

    CButton2 *button = new CButton2("alpha", 200, 90, "beta", 110, 30, 30, 30);

    mainLayout->addItem(button->layout());

=======
>>>>>>> 011a46d6151cf9c3f6f525ddff7d47fd85a0c355:src/component/page/duisettingspage.cpp
    m_DesktopViewport = new DuiPannableViewport(Qt::Vertical, this);
}




void DuiSettingsPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);
    qDebug() << "WARNING: orientation change is not yet implemented";
}

