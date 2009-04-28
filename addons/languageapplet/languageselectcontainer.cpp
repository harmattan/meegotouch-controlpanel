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
    
    GroupTitleWidget *titleLabel = new GroupTitleWidget(m_TitleText, this);
    mainLayoutPolicy->addItemAtPosition(titleLabel, 0);

    // gridLayout
    DuiLayout *gridLayout = new DuiLayout(NULL);
    gridLayout->setAnimator(NULL);
    DuiGridLayoutPolicy *itemLayout = new DuiGridLayoutPolicy(gridLayout);
    gridLayout->setPolicy(itemLayout);
    
    QStringListIterator iterator(m_ItemList);
    while (iterator.hasNext()) {
        QString langCode = iterator.next();
        m_ListItemVector.append(new LanguageListItem(langCode,
                                DcpLanguageConf::fullName(langCode), this));
    }

    for (int i = 0; i < m_ListItemVector.size(); i++) {
        itemLayout->addItemAtPosition(m_ListItemVector[i], i / 2, i % 2);
        connect(m_ListItemVector[i], SIGNAL(clicked(LanguageListItem *)), 
                this, SLOT(itemClicked(LanguageListItem *)));
    }
    
    mainLayoutPolicy->addItemAtPosition(gridLayout, 1);
    this->setLayout(mainLayout);
}

void LanguageSelectContainer::itemClicked(LanguageListItem *item)
{
    item->checked(true);
    DcpLanguageConf::instance()->setDisplayLanguage(item->langCode());
    emit changeBackToMain();
}
