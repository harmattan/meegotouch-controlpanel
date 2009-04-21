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
                         m_titleText(title),
                         m_itemList(itemList)
{
    initWidget();
    this->selectItem(DcpLanguageConf::instance()->displayLanguage());
}

LanguageSelectContainer::~LanguageSelectContainer()
{
}

void LanguageSelectContainer::selectItem(const QString &text)
{
    for (int i = 0; i < m_listItemVector.size(); i++)
    {
        if (text == m_listItemVector[i]->text())
        {
            m_listItemVector[i]->checked(true);
        }
    }
}

void LanguageSelectContainer::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    
    GroupTitleWidget *titleLabel = new GroupTitleWidget(m_titleText, this);
    mainLayoutPolicy->addItemAtPosition(titleLabel, 0, Qt::AlignCenter);

    // gridLayout
    DuiLayout *gridLayout = new DuiLayout(NULL);
    DuiGridLayoutPolicy *itemLayout = new DuiGridLayoutPolicy(gridLayout);
    gridLayout->setPolicy(itemLayout);
    
    QStringListIterator iterator(m_itemList);
    while (iterator.hasNext())
    {
        QString name = iterator.next();
        m_listItemVector.append(new LanguageListItem(name, this));
    }

    for (int i = 0; i < m_listItemVector.size(); i++)
    {
        itemLayout->addItemAtPosition(m_listItemVector[i], i / 2, i % 2);
        connect(m_listItemVector[i], SIGNAL(clicked(LanguageListItem *)), 
                this, SLOT(itemClicked(LanguageListItem *)));
    }

    mainLayoutPolicy->addItemAtPosition(gridLayout, 1, Qt::AlignCenter);
}

void LanguageSelectContainer::itemClicked(LanguageListItem *item)
{
    item->checked(true);
    DcpLanguageConf::instance()->setDisplayLanguage(item->text());
    emit changeBackToMain();
}
