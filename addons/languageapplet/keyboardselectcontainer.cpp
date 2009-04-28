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
#include <DuiMessageBox>

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
  /*  while (iterator.hasNext())
        if (m_listItems.contains(iterator.next()))
            m_listItems[iterator.next()]->checked(true);
    */
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
    
    GroupTitleWidget *titleLabel = new GroupTitleWidget(m_titleText, this);
    mainLayoutPolicy->addItemAtPosition(titleLabel, 0, Qt::AlignCenter);

    // gridLayout
    DuiLayout *gridLayout = new DuiLayout(NULL);
    gridLayout->setAnimator(NULL);
    DuiGridLayoutPolicy *itemLayout = new DuiGridLayoutPolicy(gridLayout);
    gridLayout->setPolicy(itemLayout);
    
    QStringListIterator iterator(m_itemList);
    int i=0;
    while (iterator.hasNext())
    {
        QString langCode = iterator.next();
        LanguageListItem *item = new LanguageListItem(langCode, 
            DcpLanguageConf::fullName(langCode), this);
        m_listItems[langCode] = item;
        itemLayout->addItemAtPosition(item, i / 2, i % 2);
        connect(item, SIGNAL(clicked(LanguageListItem*)), this,
                SLOT(itemClicked(LanguageListItem*)));
        i++;
    }


    DuiWidget* gridWidget = new DuiWidget(this);
    gridWidget->setLayout(gridLayout);
    mainLayoutPolicy->addItemAtPosition(gridWidget, 1, Qt::AlignCenter);
}

void KeyboardSelectContainer::itemClicked(LanguageListItem* item)
{
    if (item->isChecked())  
        {      
            DcpLanguageConf::instance()->addKeyboardLanguage(item->langCode());
        } else {
            bool doKeep = false;
            if (DcpLanguageConf::instance()->keyboardLanguagesNumber() == 1)
            {
                DuiMessageBox mb("Keep last language?",
                                 DuiMessageBox::Ok|DuiMessageBox::Cancel);
                mb.setParent(this);                
                mb.exec();
                doKeep = mb.result() != DuiDialog::Accepted;
                }
            if (doKeep)
               item->checked(true);
            else
                DcpLanguageConf::instance()->removeKeyboardLanguage(item->langCode());
        }
    }

