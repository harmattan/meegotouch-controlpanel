#include "keyboarddialog.h"
#include "dcplanguageselectcontainer.h"
#include "languagetranslation.h"
#include "dcplanguage.h"
#include "dcplanguageconf.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>

KeyboardDialog::KeyboardDialog()
              :DcpCommonDialog(DcpLanguage::SelectKeyboardText),
               m_SelectContainer(NULL)
{
    initWidget();
}

KeyboardDialog::~KeyboardDialog()
{
}

void KeyboardDialog::initWidget()
{
    // centralWidget
    DuiWidget *centralWidget = new DuiWidget(this);
    m_WidgetLayout = new DuiLayout(centralWidget);
    m_WidgetLayout->setAnimator(0);
    DuiLinearLayoutPolicy *widgetLayoutPolicy = 
        new DuiLinearLayoutPolicy(m_WidgetLayout, Qt::Vertical);
    m_WidgetLayout->setPolicy(widgetLayoutPolicy);
    centralWidget->setLayout(m_WidgetLayout);
    setContentsMargins(0.0, 0.0, 0.0, 0.0);
    widgetLayoutPolicy->setSpacing(5);

    // KeyboardSelectContainer
    m_SelectContainer = 
        new DcpLanguageSelectContainer(DcpLanguageSelectContainer::MultiSelect, centralWidget);

    // Add items to widgetLayoutPolicy
    widgetLayoutPolicy->addItemAtPosition(m_SelectContainer, 0, Qt::AlignCenter);

    // setCentralWidget
    this->setCentralWidget(centralWidget);
}

QStringList KeyboardDialog::selectedLanguages()
{
    Q_ASSERT(m_SelectContainer);
    return m_SelectContainer->selectedLanguages();
}
