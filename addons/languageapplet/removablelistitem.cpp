#include "removablelistitem.h"
#include "languagelabel.h"
#include "dcpspaceritem.h"
#include "languagetranslation.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duibutton.h>

const int buttonWidth  = 230;
const int buttonHeight =  40;

RemovableListItem::RemovableListItem(const QString &upText,
                                     const QString &downText,
                                     DuiWidget *parent)
                  :DuiWidget(parent),
                   m_upText(upText),
                   m_downText(downText)
{
    initWidget();
}

RemovableListItem::RemovableListItem(const QString &text,
                                     DuiWidget *parent)
                  :DuiWidget(parent),
                   m_upText(text),
                   m_downText(QString(""))
{
    initWidget();
}

RemovableListItem::~RemovableListItem()
{
}

void RemovableListItem::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Horizontal);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    mainLayoutPolicy->setSpacing(1);

    // label
    LanguageLabel *label = NULL;
    if (m_downText.isEmpty())
    {
        label = new LanguageLabel(m_upText, this);
    } else {
        label = new LanguageLabel(m_upText, m_downText, this);
    }

    // button
    m_removeButton = new DuiButton(DcpLanguage::RemoveButtonText, this);
    m_removeButton->setMaximumWidth(buttonWidth);
    m_removeButton->setMinimumWidth(buttonWidth);
    m_removeButton->setMaximumHeight(buttonHeight);
    m_removeButton->setMinimumHeight(buttonHeight);
    m_removeButton->setObjectName("RemoveButton");
    connect(m_removeButton, SIGNAL(clicked()), this, SLOT(removeClicked()));

    mainLayoutPolicy->addItemAtPosition(label, 0, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 10, QSizePolicy::Expanding, QSizePolicy::Fixed),
                    1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_removeButton, 2, Qt::AlignRight | Qt::AlignVCenter);
    
    this->setLayout(mainLayout);
}

void RemovableListItem::removeClicked()
{
    emit clicked(this);
}
