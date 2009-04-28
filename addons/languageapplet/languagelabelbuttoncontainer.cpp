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
                             m_Type(type)
{
    initWidget();
}

LanguageLabelButtonContainer::~LanguageLabelButtonContainer()
{
}

void LanguageLabelButtonContainer::initWidget()
{
    // mainLayout
    m_MainLayout = new DuiLayout(this);
    m_MainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(m_MainLayout, Qt::Vertical);
    m_MainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(1.0, 0.0, 1.0, 0.0);
    mainLayoutPolicy->setSpacing(2);

    // group title
    GroupTitleWidget *titleLabel = NULL;
    switch (m_Type) {
        case LanguageLabelButtonContainer::DOWNLOADED:
                titleLabel = new GroupTitleWidget(DcpLanguage::DownloadedText, this);
                m_ItemVector.push_back(new RemovableListItem("Magyar", "Version 0.2", this));
                break;
        case LanguageLabelButtonContainer::INSTALLED:
                titleLabel = new GroupTitleWidget(DcpLanguage::InstalledText, this);
                m_ItemVector.push_back(new RemovableListItem("Language 1", this));
                m_ItemVector.push_back(new RemovableListItem("Language 2", this));
                break;
        default:
                break;
    }

    mainLayoutPolicy->addItemAtPosition(titleLabel, 0, Qt::AlignCenter);
    for (int i = 0; i < m_ItemVector.size(); i++)
    {
        mainLayoutPolicy->addItemAtPosition(m_ItemVector[i], i + 1, Qt::AlignCenter);
        connect(m_ItemVector[i], SIGNAL(clicked(RemovableListItem*)), 
                this, SLOT(deleteItem(RemovableListItem*)));
    }
    
    this->setLayout(m_MainLayout);
}

void LanguageLabelButtonContainer::deleteItem(RemovableListItem *item)
{
   if (m_ItemVector.contains(item))
   {
        item->hide();
        m_ItemVector.remove(m_ItemVector.indexOf(item));
        int index = m_MainLayout->findIndexForItem(static_cast<QGraphicsItem*>(item));
        if (index != -1)
            m_MainLayout->removeAt(index);
        
        if (m_ItemVector.isEmpty())
        {
            emit removeMe(this);
        }
   }
}
