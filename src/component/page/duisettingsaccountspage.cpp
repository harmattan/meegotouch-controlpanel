#include "duisettingsaccountspage.h"
#include "duisimplecategory.h"
#include "duimaincategory.h"
#include <QtDebug>



DuiSettingsAccountPage::DuiSettingsAccountPage() : DuiSettingsCategoryPage() 
{
}


void DuiSettingsAccountPage::createContent()
{
    DuiSettingsCategoryPage::createContent();
    m_Category->setTitle(tr("Accounts"));
    for (int i=0; i<10;i++){
        if (i%2){
            DuiSimpleCategory *c2 = new DuiSimpleCategory("Two in a row1");
            DuiSimpleCategory *c3 = new DuiSimpleCategory("Tow in a row2");
            m_Category->add(c2, c3);
        } else {
            DuiSimpleCategory *c1 = new DuiSimpleCategory("One in a row");
            m_Category->add(c1);
        }
    }

}

