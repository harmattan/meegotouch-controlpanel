#include <QtDebug>
#include <duipannableviewport.h>

#include <duibutton.h>

#include <QGridLayout>

#include "duisimplecategory.h"
#include "duimaincategory.h"
#include "duiwidgetview.h"

#include "duisettingspage.h"
#include "duibackgroundview.h"


#include "button2.h"

DuiSettingsPage::DuiSettingsPage()
{
}


void DuiSettingsPage::createContent()
{
   /*
    DuiLinearLayout* mainLayout = new DuiLinearLayout(Qt::Vertical);

    DuiLabel* title = new DuiLabel("Title");
    title->setAlignment(Qt::AlignCenter);
    title->setMaximumHeight(130);

    title->setMinimumWidth(300);

    mainLayout->addItem(title);

    CButton2 *button = new CButton2("alpha", 200, 90, "beta", 110, 30, 30, 30);

    mainLayout->addItem(button->layout());*/


    m_DesktopViewport = new DuiPannableViewport(Qt::Vertical, this);
    DuiBackgroundView *view = new DuiBackgroundView(*m_DesktopViewport);
    m_DesktopViewport->setView(view);
}




void DuiSettingsPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);
    qDebug() << "WARNING: orientation change is not yet implemented";
}

