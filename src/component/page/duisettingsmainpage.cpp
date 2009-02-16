#include "duisettingsmainpage.h"

#include <QtDebug>

#include <duilinearlayout.h>
#include <duilabel.h>
#include "duisimplecategory.h"
#include <duipannableviewport.h>


DuiSettingsMainPage::DuiSettingsMainPage()
{
}


void DuiSettingsMainPage::createContent()
{
    DuiSettingsPage::createContent();
    DuiLinearLayout* mainLayout = new DuiLinearLayout(Qt::Vertical);

    DuiLabel* title = new DuiLabel("Title");
    title->setAlignment(Qt::AlignCenter);
    title->setMaximumHeight(30);
    mainLayout->addItem(title);

    DuiSimpleCategory *category = new DuiSimpleCategory("Example");
    DuiSimpleCategory *subcategory = new DuiSimpleCategory("SubCategory");
    category->add(subcategory);
    m_Viewport->setWidget(category);
    
    mainLayout->addItem(m_Viewport);

    setLayout(mainLayout);
}



