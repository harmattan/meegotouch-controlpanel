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
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(m_mainLayout, Qt::Vertical);
    m_mainLayout->setPolicy(mainLayoutPolicy);

    // group title
    GroupTitleWidget *titleLabel = NULL;
    RemovableListItem *removeItem = NULL;
    switch (m_type)
    {
        case LanguageLabelButtonContainer::DOWNLOADED:
                titleLabel = new GroupTitleWidget(DcpLanguage::DownloadedText, this);
                removeItem = new RemovableListItem("Hungarian", "Version 0.2", this);
                break;
        case LanguageLabelButtonContainer::INSTALLED:
                titleLabel = new GroupTitleWidget(DcpLanguage::InstalledText, this);
                removeItem = new RemovableListItem("Language", this);
                break;
        default:
                break;
    }
    connect(removeItem, SIGNAL(clicked(int)), this, SLOT(deleteItem(int)));

    mainLayoutPolicy->addItemAtPosition(titleLabel, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(removeItem, 1, Qt::AlignCenter);
    removeItem->setId(1);
    
    this->setLayout(m_mainLayout);
}

void LanguageLabelButtonContainer::deleteItem(int id)
{
    if (id >= 0)
    {
        m_mainLayout->removeAt(id);
    }
}
