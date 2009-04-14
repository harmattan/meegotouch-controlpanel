#include "keyboardselectcontainer.h"
#include "languagelistitem.h"
#include "grouptitlewidget.h"
#include "dcplanguageconf.h"

#include <QDebug>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duigridlayoutpolicy.h>
#include <duilabel.h>

KeyboardSelectContainer::KeyboardSelectContainer(const QString &title,
                                                 QStringList itemList,
                                                 DuiWidget *parent)
                        :DuiWidget(parent),
                         m_titleText(title),
                         m_itemList(itemList)
{
    initWidget();
    QStringList keyboardList = DcpLanguageConf::instance()->keyboardLanguages();
    QStringListIterator iterator(keyboardList);
    while (iterator.hasNext())
    {
        this->selectItem(iterator.next());
    }
}

KeyboardSelectContainer::~KeyboardSelectContainer()
{
}

void KeyboardSelectContainer::selectItem(const QString &text)
{
    for (int i = 0; i < m_listItemVector.size(); i++)
    {
        if (text == m_listItemVector[i]->text())
        {
            m_listItemVector[i]->checked(true);
        }
    }
}

void KeyboardSelectContainer::initWidget()
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
        connect(m_listItemVector[i], SIGNAL(clicked()), this, SLOT(itemClicked()));
    }

    mainLayoutPolicy->addItemAtPosition(gridLayout, 1, Qt::AlignCenter);
}

void KeyboardSelectContainer::itemClicked()
{
    for (int i = 0; i < m_listItemVector.size(); i++)
    {
        if (m_listItemVector[i]->isChecked())
        {
            DcpLanguageConf::instance()->removeKeyboardLanguage(m_listItemVector[i]->text());
            DcpLanguageConf::instance()->addKeyboardLanguage(m_listItemVector[i]->text());
        } else {
            DcpLanguageConf::instance()->removeKeyboardLanguage(m_listItemVector[i]->text());
        }
    }
}
