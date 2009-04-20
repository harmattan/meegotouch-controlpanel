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
    DuiLayout *mainLayout = new DuiLayout(this);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);

    // group title
    GroupTitleWidget *titleLabel = NULL;
    RemovableListItem *removeItem = NULL;
    switch (m_type)
    {
        case LanguageLabelButtonContainer::DOWNLOADED:
                titleLabel = new GroupTitleWidget(DcpLanguage::DownloadedText, this);
                removeItem = new RemovableListItem("Deutsch", "Version 0.2", this);
                break;
        case LanguageLabelButtonContainer::INSTALLED:
                titleLabel = new GroupTitleWidget(DcpLanguage::InstalledText, this);
                removeItem = new RemovableListItem("Language", this);
                break;
        default:
                break;
    }

    mainLayoutPolicy->addItemAtPosition(titleLabel, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(removeItem, 1, Qt::AlignCenter);
}
