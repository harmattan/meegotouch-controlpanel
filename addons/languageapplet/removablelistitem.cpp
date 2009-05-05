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
                   m_UpText(upText),
                   m_DownText(downText)
{
    initWidget();
}

RemovableListItem::RemovableListItem(const QString &text,
                                     DuiWidget *parent)
                  :DuiWidget(parent),
                   m_UpText(text),
                   m_DownText(QString(""))
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
    mainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Horizontal);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    mainLayoutPolicy->setSpacing(1);

    // label
    LanguageLabel *label = NULL;
    if (m_DownText.isEmpty())
    {
        label = new LanguageLabel(m_UpText, this);
    } else {
        label = new LanguageLabel(m_UpText, m_DownText, this);
    }

    // button
    m_RemoveButton = new DuiButton(DcpLanguage::RemoveButtonText, this);
    m_RemoveButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_RemoveButton->setMaximumWidth(buttonWidth);
    m_RemoveButton->setMinimumWidth(buttonWidth);
    m_RemoveButton->setMaximumHeight(buttonHeight);
    m_RemoveButton->setMinimumHeight(buttonHeight);
    m_RemoveButton->setObjectName("RemoveButton");
    connect(m_RemoveButton, SIGNAL(clicked()), this, SLOT(removeClicked()));

    mainLayoutPolicy->addItemAtPosition(label, 0, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 140, 5, QSizePolicy::Fixed, QSizePolicy::Fixed),
            1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_RemoveButton, 2, Qt::AlignRight | Qt::AlignVCenter);
    
    this->setLayout(mainLayout);
}

void RemovableListItem::removeClicked()
{
    emit clicked(this);
}
