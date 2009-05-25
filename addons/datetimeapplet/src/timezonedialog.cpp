#include "timezonedialog.h"
#include "datetimetranslation.h"
#include "dcpspaceritem.h"
#include "timezonecontainer.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duitextedit.h>

TimeZoneDialog::TimeZoneDialog()
               :DcpCommonDialog(DcpDateTime::TimeZoneTitle)
{
    initWidget();
}

TimeZoneDialog::~TimeZoneDialog()
{
}

void TimeZoneDialog::initWidget()
{
    // centralWidget
    DuiWidget *centralWidget = new DuiWidget(this);
    DuiLayout *mainLayout = new DuiLayout(centralWidget);
    centralWidget->setLayout(mainLayout);
    mainLayout->setAnimator(0);
    mainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
        new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setSpacing(3);

    // textEdit
    DuiTextEdit *textEdit = new DuiTextEdit(DuiTextEditModel::SingleLine, 
            DcpDateTime::InputCountryText, centralWidget);
    textEdit->setObjectName("InputTextEdit");
    textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // timeZoneContainer
    TimeZoneContainer *timeZoneContainer = new TimeZoneContainer(this);
    
    // Add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(textEdit, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(timeZoneContainer, 1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(centralWidget, 5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding),
            2, Qt::AlignCenter);
    
    // setCentralWidget
    this->setCentralWidget(centralWidget);
}

