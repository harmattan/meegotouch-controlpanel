#include "languageselectcontainer.h"
#include "languagelistitem.h"

#include <duilinearlayout.h>
#include <duigridlayout.h>
#include <duilabel.h>

LanguageSelectContainer::LanguageSelectContainer(const QString &title,
                                                 QStringList itemList,
                                                 DuiWidget *parent)
                        :DuiWidget(parent),
                         m_titleText(title),
                         m_itemList(itemList)
{
    initWidget();
}

LanguageSelectContainer::~LanguageSelectContainer()
{
}

void LanguageSelectContainer::initWidget()
{
    // mainLayout
    DuiLinearLayout *mainLayout = new DuiLinearLayout(Qt::Vertical, this);
    
    // titleLayout
    DuiLinearLayout *titleLayout = new DuiLinearLayout(Qt::Horizontal, NULL);

    DuiLabel *titleLabel = new DuiLabel(m_titleText, this);
    titleLabel->setObjectName("DisplayLanguageSelectTitle");
    titleLayout->addItem(titleLabel);
    titleLayout->setAlignment(titleLabel, Qt::AlignLeft | Qt::AlignVCenter);

    mainLayout->addItem(titleLayout);

    // gridLayout
    DuiGridLayout *itemLayout = new DuiGridLayout(NULL);
    
    QStringListIterator iterator(m_itemList);
    while (iterator.hasNext())
    {
        QString name = iterator.next();
        m_listItemVector.append(new LanguageListItem(name, false, this));
    }

    for (int i = 0; i < m_listItemVector.size(); i++)
    {
        itemLayout->addItem(m_listItemVector[i], i / 2, i % 2, Qt::AlignCenter);
    }

    mainLayout->addItem(itemLayout);
    mainLayout->setAlignment(itemLayout, Qt::AlignCenter);
}
