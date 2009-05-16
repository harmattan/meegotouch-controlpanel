#include "displaydialog.h"
#include "languagetranslation.h"
#include "dcplanguageselectcontainer.h"
#include "dcplanguage.h"
#include "dcplanguageconf.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>

DisplayDialog::DisplayDialog()
              :CommonDialog(DcpLanguage::SelectDisplayText)
{
    initWidget();
}

DisplayDialog::~DisplayDialog()
{
}

void DisplayDialog::initWidget()
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

    // LanguageSelectContainer
    DcpLanguageSelectContainer *selectCont =
        new DcpLanguageSelectContainer(DcpLanguageSelectContainer::SingleSelect, centralWidget);
    connect(selectCont, SIGNAL(closing()), this, SLOT(accept()));

    // Add item to widgetLayoutPolicy
    widgetLayoutPolicy->addItemAtPosition(selectCont, 0, Qt::AlignCenter);

    // setCentralWidget
    this->setCentralWidget(centralWidget);
}
