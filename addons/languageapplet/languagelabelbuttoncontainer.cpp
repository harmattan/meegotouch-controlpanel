#include "languagelabelbuttoncontainer.h"
#include "grouptitlewidget.h"
#include "removablelistitem.h"
#include "languagetranslation.h"
#include "dcpspaceritem.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>


LanguageLabelButtonContainer::LanguageLabelButtonContainer(LanguageLabelButtonContainer::Type type,
                                                         DuiWidget *parent)
                            :DuiWidget(parent),
                             m_type(type)
{
    initWidget();
}

LanguageLabelButtonContainer::~LanguageLabelButtonContainer()
{
}

void LanguageLabelButtonContainer::initWidget()
{
    // mainLayout
    m_mainLayout = new DuiLayout(this);
    m_mainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(m_mainLayout, Qt::Vertical);
    m_mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(1.0, 0.0, 1.0, 0.0);
    mainLayoutPolicy->setSpacing(2);

    // group title
    GroupTitleWidget *titleLabel = NULL;
    switch (m_type)
    {
        case LanguageLabelButtonContainer::DOWNLOADED:
                titleLabel = new GroupTitleWidget(DcpLanguage::DownloadedText, this);
                m_itemVector.push_back(new RemovableListItem("Magyar", "Version 0.2", this));
                break;
        case LanguageLabelButtonContainer::INSTALLED:
                titleLabel = new GroupTitleWidget(DcpLanguage::InstalledText, this);
                m_itemVector.push_back(new RemovableListItem("Language 1", this));
                m_itemVector.push_back(new RemovableListItem("Language 2", this));
                break;
        default:
                break;
    }

    mainLayoutPolicy->addItemAtPosition(titleLabel, 0, Qt::AlignCenter);
    for (int i = 0; i < m_itemVector.size(); i++)
    {
        mainLayoutPolicy->addItemAtPosition(m_itemVector[i], i + 1, Qt::AlignCenter);
        connect(m_itemVector[i], SIGNAL(clicked(RemovableListItem*)), 
                this, SLOT(deleteItem(RemovableListItem*)));
    }
    
    this->setLayout(m_mainLayout);
}

void LanguageLabelButtonContainer::deleteItem(RemovableListItem *item)
{
   if (m_itemVector.contains(item))
   {
        item->hide();
        m_itemVector.remove(m_itemVector.indexOf(item));
        int index = m_mainLayout->findIndexForItem(static_cast<QGraphicsItem*>(item));
        if (index != -1)
            m_mainLayout->removeAt(index);
        
        if (m_itemVector.isEmpty())
        {
            emit removeMe(this);
        }
   }
}
