#include "dcplanguageselectcontainer.h"
#include "dcplanguageconf.h"
#include "languagelistitem.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duigridlayoutpolicy.h>
#include <duiscenemanager.h>

DcpLanguageSelectContainer::DcpLanguageSelectContainer(DcpLanguageSelectContainer::Type type,
                                                       DuiWidget *parent)
                           :DuiWidget(parent),
                            m_Type(type)
{
    initWidget();
    initCheckedItems();
}

DcpLanguageSelectContainer::~DcpLanguageSelectContainer()
{
}

QStringList DcpLanguageSelectContainer::selectedLanguages()
{
    QStringList resultList;
    for (int i = 0; i < m_ItemLayout->count(); i++) {
        LanguageListItem *item = static_cast<LanguageListItem*>(m_PortraitPolicy->itemAt(i));
        Q_ASSERT(item != 0);
        if (item->isChecked()) {
            resultList << item->langCode();
        }
    }

    return resultList;
}

void DcpLanguageSelectContainer::initWidget()
{
    // m_ItemLayout
    m_ItemLayout = new DuiLayout(this);
    m_ItemLayout->setAnimator(0);
    setLayout(m_ItemLayout);
    m_ItemLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);

    // m_LandscapePolicy
    m_LandscapePolicy = new DuiGridLayoutPolicy(m_ItemLayout);
    m_LandscapePolicy->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    m_LandscapePolicy->setSpacing(10);
    m_LandscapePolicy->setColumnStretchFactor(0, 1); // forces same size
    m_LandscapePolicy->setColumnStretchFactor(1, 1);

    // m_PortraitPolicy
    m_PortraitPolicy = new DuiLinearLayoutPolicy(m_ItemLayout, Qt::Vertical);
    m_PortraitPolicy->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    m_PortraitPolicy->setSpacing(1);

    // Add items to layoutPolicies
    QStringList availableList;
    switch (m_Type) {
        case DcpLanguageSelectContainer::SingleSelect:
            availableList = DcpLanguageConf::instance()->availableInputLanguages();
            break;
        case DcpLanguageSelectContainer::MultiSelect:
            availableList = DcpLanguageConf::instance()->availableKeyboardLanguages();
            break;
        default:
            break;
    }

    QStringListIterator iterator(availableList);
    int index = 0;
    while (iterator.hasNext()) {
        QString langCode = iterator.next();
        LanguageListItem *item = 
            new LanguageListItem(langCode, DcpLanguageConf::fullName(langCode), this);
        if (m_Type == DcpLanguageSelectContainer::SingleSelect) {
            connect(item, SIGNAL(clicked(LanguageListItem*)), 
                    this, SLOT(itemClicked(LanguageListItem*)));
        }

        // add item to map.
        m_ItemMap[langCode] = item;
        m_LandscapePolicy->addItemAtPosition(item, index / 2, index % 2);
        m_PortraitPolicy->addItemAtPosition(item, index, Qt::AlignCenter);
        index++;
    }

    // orientation change
    connect(DuiSceneManager::instance(), SIGNAL(orientationChanged(const Dui::Orientation &)),
            this, SLOT(orientationChanged()));
    orientationChanged();
}

void DcpLanguageSelectContainer::initCheckedItems()
{
    // set checked items
    QStringList langList;
    switch (m_Type) {
        case DcpLanguageSelectContainer::SingleSelect :
            langList << DcpLanguageConf::instance()->displayLanguage();
            break;
        case DcpLanguageSelectContainer::MultiSelect :
            langList = DcpLanguageConf::instance()->keyboardLanguages();
            break;
        default:
            break;
    }

    QStringListIterator iterator(langList);
    while (iterator.hasNext()) {
        QString langCode = iterator.next();
        if (m_ItemMap.contains(langCode)) {
            m_ItemMap[langCode]->checked(true);
        }
    }
}

void DcpLanguageSelectContainer::orientationChanged()
{
    if (DuiSceneManager::instance()==0) return;

    int itemNum = m_ItemLayout->count();
    switch (DuiSceneManager::instance()->orientation()) {
        case Dui::Landscape:
            m_ItemLayout->setPolicy(m_LandscapePolicy);
            if (itemNum > 0) {
                if (itemNum % 2 == 0) {
                    static_cast<LanguageListItem*>(m_PortraitPolicy->itemAt(itemNum - 2))->setVisibleSeparator(false);
                    static_cast<LanguageListItem*>(m_PortraitPolicy->itemAt(itemNum - 1))->setVisibleSeparator(false);
                } else {
                    static_cast<LanguageListItem*>(m_PortraitPolicy->itemAt(itemNum - 1))->setVisibleSeparator(false);
                }
            }
            break;
        case Dui::Portrait:
            m_ItemLayout->setPolicy(m_PortraitPolicy);
            if (itemNum > 1) {
                static_cast<LanguageListItem*>(m_PortraitPolicy->itemAt(itemNum - 2))->setVisibleSeparator(true);
            }
            if (itemNum > 0) {
                static_cast<LanguageListItem*>(m_PortraitPolicy->itemAt(itemNum - 1))->setVisibleSeparator(false);
            }
            break;
        default:
            break;
    }
}

void DcpLanguageSelectContainer::itemClicked(LanguageListItem *item)
{
    item->checked(true);
    DcpLanguageConf::instance()->setDisplayLanguage(item->langCode());
    emit closing();
}
