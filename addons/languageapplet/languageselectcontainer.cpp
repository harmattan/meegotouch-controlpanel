#include "languageselectcontainer.h"
#include "languagelistitem.h"
#include "grouptitlewidget.h"
#include "dcplanguageconf.h"

#include <QDebug>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duigridlayoutpolicy.h>
#include <duilabel.h>

LanguageSelectContainer::LanguageSelectContainer(const QString &title,
                                                 QStringList itemList,
                                                 DuiWidget *parent)
                        :DuiWidget(parent),
                         m_TitleText(title),
                         m_ItemList(itemList)
{
    initWidget();
    this->selectItem(DcpLanguageConf::instance()->displayLanguage());
}

LanguageSelectContainer::~LanguageSelectContainer()
{
}

void LanguageSelectContainer::selectItem(const QString &text)
{
    for (int i = 0; i < m_ListItemVector.size(); i++)
    {
        if (text == m_ListItemVector[i]->langCode())
        {
            m_ListItemVector[i]->checked(true);
        }
    }
}

void LanguageSelectContainer::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    
    GroupTitleWidget *titleLabel = new GroupTitleWidget(m_TitleText, this);
    mainLayoutPolicy->addItemAtPosition(titleLabel, 0, Qt::AlignCenter);

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
    while (iterator.hasNext()) {
        QString langCode = iterator.next();
        m_ListItemVector.append(new LanguageListItem(langCode,
                                DcpLanguageConf::fullName(langCode), this));
    }

    for (int i = 0; i < m_ListItemVector.size(); i++) {
        m_LandscapePolicy->addItemAtPosition(m_ListItemVector[i], i / 2, i % 2);
        m_PortraitPolicy->addItemAtPosition(m_ListItemVector[i], i, Qt::AlignCenter);
        connect(m_ListItemVector[i], SIGNAL(clicked(LanguageListItem *)), 
                this, SLOT(itemClicked(LanguageListItem *)));
    }
    
    mainLayoutPolicy->addItemAtPosition(m_ItemLayout, 1);
    this->setLayout(mainLayout);

    // orientation
    connect(DuiDeviceProfile::instance(), SIGNAL(orientationAngleChanged(DuiDeviceProfile::DeviceOrientationAngle)),
            this, SLOT(onOrientationAngleChange()));
    onOrientationAngleChange();
}

void LanguageSelectContainer::itemClicked(LanguageListItem *item)
{
    item->checked(true);
    DcpLanguageConf::instance()->setDisplayLanguage(item->langCode());
    emit changeBackToMain();
}

void LanguageSelectContainer::onOrientationAngleChange()
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
