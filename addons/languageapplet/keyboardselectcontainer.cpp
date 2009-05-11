#include "keyboardselectcontainer.h"
#include "languagelistitem.h"
#include "grouptitlewidget.h"
#include "dcplanguageconf.h"
#include "languagetranslation.h"

#include <QDebug>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duigridlayoutpolicy.h>
#include <duilabel.h>
#include <duilocale.h>

KeyboardSelectContainer::KeyboardSelectContainer(const QString &title,
                                                 QStringList itemList,
                                                 DuiWidget *parent)
                        :DuiWidget(parent),
                         m_TitleText(title),
                         m_ItemList(itemList)
{
    initWidget();
    QStringList keyboardList = DcpLanguageConf::instance()->keyboardLanguages();
    QStringListIterator iterator(keyboardList);
    while (iterator.hasNext()) {
        QString langCode = iterator.next();
        if (m_ListItems.contains(langCode)) {
            m_ListItems[langCode]->checked(true);
        }
    }
}

KeyboardSelectContainer::~KeyboardSelectContainer()
{
}

void KeyboardSelectContainer::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    
    /* GroupTitleWidget *titleLabel = new GroupTitleWidget(m_TitleText, this);
    mainLayoutPolicy->addItemAtPosition(titleLabel, 0, Qt::AlignCenter);*/

    // m_ItemLayout
    m_ItemLayout = new DuiLayout(NULL);
    m_ItemLayout->setAnimator(NULL);
    m_LandscapePolicy = new DuiGridLayoutPolicy(m_ItemLayout);
    m_ItemLayout->setPolicy(m_LandscapePolicy);
    m_LandscapePolicy->setContentsMargins(0.0, 0.0, 0.0, 0.0);

    // m_PortraitPolicy
    m_PortraitPolicy = new DuiLinearLayoutPolicy(m_ItemLayout, Qt::Vertical);
    m_PortraitPolicy->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    
    QStringListIterator iterator(m_ItemList);
    int i = 0;
    while (iterator.hasNext()) {
        QString langCode = iterator.next();
        LanguageListItem *item = new LanguageListItem(langCode, 
            DcpLanguageConf::fullName(langCode), this);
        m_ListItems[langCode] = item;
        m_LandscapePolicy->addItemAtPosition(item, i / 2, i % 2);
        m_PortraitPolicy->addItemAtPosition(item, i, Qt::AlignCenter);
        connect(item, SIGNAL(clicked(LanguageListItem*)), this,
                SLOT(itemClicked(LanguageListItem*)));
        i++;
    }

    mainLayoutPolicy->addItemAtPosition(m_ItemLayout, 1, Qt::AlignCenter);
    this->setLayout(mainLayout);

    connect(DuiDeviceProfile::instance(), SIGNAL(orientationAngleChanged(DuiDeviceProfile::DeviceOrientationAngle)),
            this, SLOT(onOrientationAngleChange()));
    onOrientationAngleChange();
}

void KeyboardSelectContainer::itemClicked(LanguageListItem* item)
{
    if (item->isChecked()) {
        DcpLanguageConf::instance()->addKeyboardLanguage(item->langCode());
    } else {
            m_LastRemovedLangCode = item->langCode();
            DcpLanguageConf::instance()->removeKeyboardLanguage(item->langCode());
    }
}

void KeyboardSelectContainer::onOrientationAngleChange()
{
    switch(DuiDeviceProfile::instance()->orientation()) {
        case Dui::Landscape:
            m_ItemLayout->setPolicy(m_LandscapePolicy);
            break;
        case Dui::Portrait:
            m_ItemLayout->setPolicy(m_PortraitPolicy);
            break;
        default:
            break;
    }
}

void KeyboardSelectContainer::putLastLanguageBack()
{
    DcpLanguageConf::instance()->addKeyboardLanguage(m_LastRemovedLangCode);

};
