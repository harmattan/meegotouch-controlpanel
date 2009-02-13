#include "duisettingspage.h"

#include <QtDebug>

#include <duilinearlayout.h>
#include <duilabel.h>
#include <duipannableviewport.h>

#include "duisimplecategory.h"

DuiSettingsPage::DuiSettingsPage()
{
}


void DuiSettingsPage::createContent()
{
    DuiLinearLayout* mainLayout = new DuiLinearLayout(Qt::Vertical);

    DuiLabel* title = new DuiLabel("Title");
    title->setAlignment(Qt::AlignCenter);
    title->setMaximumHeight(30);
    mainLayout->addItem(title);

    DuiPannableViewport* desktopViewport = new DuiPannableViewport(Qt::Vertical, this);
    DuiSimpleCategory *category = new DuiSimpleCategory("Example");
    DuiSimpleCategory *subcategory = new DuiSimpleCategory("SubCategory");
    category->add(subcategory);
    desktopViewport->setWidget(category);
    
    mainLayout->addItem(desktopViewport);

    setLayout(mainLayout);
}


void DuiSettingsPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);  
    qDebug() << "WARNING: orientation change is not yet implemented";
}

