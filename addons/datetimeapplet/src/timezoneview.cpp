#include "timezoneview.h"
#include "dcpdatetime.h"
#include "timezonecontainer.h"
#include "timezonelistitem.h"
#include "datetimetranslation.h"
#include "dcpspaceritem.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duitextedit.h>
#include <duiscenemanager.h>
#include <QDebug>


TimeZoneView::TimeZoneView(QGraphicsWidget *parent)
             :DcpWidget(parent)
{
    setReferer(DcpDateTime::Main);
    initWidget();
}

TimeZoneView::~TimeZoneView()
{
}

void TimeZoneView::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
    mainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    this->setLayout(mainLayout);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
        new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setSpacing(10);

    // textEditLayout
    DuiLayout *textEditLayout = new DuiLayout(0);
    textEditLayout->setAnimator(0);
    textEditLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    DuiLinearLayoutPolicy *textEditLayoutPolicy =
        new DuiLinearLayoutPolicy(textEditLayout, Qt::Horizontal);
    textEditLayout->setPolicy(textEditLayoutPolicy);
    textEditLayoutPolicy->setSpacing(1);
    
    // m_TextEdit
    m_TextEdit = new DuiTextEdit(DuiTextEditModel::MultiLine,
                                 DcpDateTime::InputCountryText,
                                 this);
    m_TextEdit->setObjectName("InputTextEdit");
    m_TextEdit->setMinimumWidth(DuiSceneManager::instance()->visibleSceneRect().width() - 40);
    connect(m_TextEdit, SIGNAL(gainedFocus(DuiTextEdit *, Qt::FocusReason)),
            this, SLOT(clearTextEdit(DuiTextEdit *)));
    // connect(m_TextEdit, SIGNAL(textChanged()), this, SLOT(filteringListItems()));

    // add items to textEditLayoutPolicy
    textEditLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 10, QSizePolicy::Expanding, QSizePolicy::Fixed),
            0, Qt::AlignLeft | Qt::AlignVCenter);
    textEditLayoutPolicy->addItemAtPosition(m_TextEdit, 1, Qt::AlignCenter);
    textEditLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 10, QSizePolicy::Expanding, QSizePolicy::Fixed),
            2, Qt::AlignRight | Qt::AlignVCenter);
     
    // m_TimeZoneContainer
    // m_TimeZoneContainer = new TimeZoneContainer(this);

    TimeZoneListItem *item = new TimeZoneListItem("Haha", "ha", "Ha", this);

    // add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(textEditLayout, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(item, 1, Qt::AlignCenter);
    qDebug() << "TimeZoneView init is finished";
}

void TimeZoneView::clearTextEdit(DuiTextEdit *textEdit)
{
    if (textEdit->text() == DcpDateTime::InputCountryText) {
        textEdit->setText("");
    }
}

/*
void TimeZoneView::filteringListItems()
{
    QString sample = m_TextEdit->text();
    QMapIterator<int, TimeZoneListItem*> iter(m_TimeZoneContainer->getMap());
    while (iter.hasNext()) {
        iter.next();
        if (iter.value()->country().startsWith(sample, Qt::CaseInsensitive) ||
            iter.value()->city().startsWith(sample, Qt::CaseInsensitive)) {
            iter.value()->filtered(true);
        } else {
            iter.value()->filtered(false);
        }
    }
    
    m_TimeZoneContainer->updateLayout();
}*/
