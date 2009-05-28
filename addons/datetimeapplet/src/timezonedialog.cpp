#include "timezonedialog.h"
#include "datetimetranslation.h"
#include "dcpspaceritem.h"
#include "timezonecontainer.h"
#include "timezonelistitem.h"

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
    mainLayoutPolicy->setSpacing(10);

    // m_TextEdit
    m_TextEdit = new DuiTextEdit(DuiTextEditModel::SingleLine, 
            DcpDateTime::InputCountryText, centralWidget);
    m_TextEdit->setObjectName("InputTextEdit");
    m_TextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(m_TextEdit, SIGNAL(gainedFocus(DuiTextEdit *)), 
            this, SLOT(clearTextEdit(DuiTextEdit *)));
    connect(m_TextEdit, SIGNAL(textChanged()),
            this, SLOT(filteringListItems()));

    // timeZoneContainer
    m_TimeZoneContainer = new TimeZoneContainer(this);
    connect(m_TimeZoneContainer, SIGNAL(closing()), this, SLOT(accept()));
    
    // Add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(m_TextEdit, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_TimeZoneContainer, 1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(centralWidget, 5, 1, QSizePolicy::Expanding, QSizePolicy::Fixed),
            2, Qt::AlignCenter);
    
    // setCentralWidget
    this->setCentralWidget(centralWidget);
}

void TimeZoneDialog::clearTextEdit(DuiTextEdit *textEdit)
{
    if (textEdit->text() == DcpDateTime::InputCountryText) {
        textEdit->setText("");
    }
}

void TimeZoneDialog::filteringListItems()
{
    QString sample = m_TextEdit->text();
    QMapIterator<int, TimeZoneListItem*> iter(m_TimeZoneContainer->getMap());
    while (iter.hasNext()) {
        iter.next();
        if (iter.value()->country().startsWith(sample, Qt::CaseInsensitive) ||
            iter.value()->city().startsWith(sample, Qt::CaseInsensitive)) {
            iter.value()->setVisible(true);
        } else {
            iter.value()->setVisible(false);
        }
    }
}

