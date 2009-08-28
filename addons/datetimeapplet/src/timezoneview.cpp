#include "timezoneview.h"
#include "dcpdatetime.h"
#include "timezonecontainer.h"
#include "timezonelistitem.h"
#include "datetimetranslation.h"
#include <DcpSpacerItem>

#include <QSizePolicy>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duitextedit.h>
#include <duiscenemanager.h>
#include <qtimer.h>

TimeZoneView::TimeZoneView(QGraphicsWidget *parent)
             :DcpWidget(parent)
{
    setReferer(DcpDateTime::Main);
    initWidget();
}

TimeZoneView::~TimeZoneView()
{
}

bool TimeZoneView::back()
{
    m_TimeZoneContainer->backPushed(true);   
    return DcpWidget::back();
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
    m_TextEdit = new DuiTextEdit(DuiTextEditModel::SingleLine,
                                 DcpDateTime::InputCountryText,
                                 this);
    m_TextEdit->setObjectName("InputTextEdit");
    m_TextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(m_TextEdit, SIGNAL(gainedFocus(DuiTextEdit *, Qt::FocusReason)),
            this, SLOT(clearTextEdit(DuiTextEdit *)));
    connect(m_TextEdit, SIGNAL(textChanged()), this, SLOT(filteringListItems()));

    // add items to textEditLayoutPolicy
    textEditLayoutPolicy->addItemAtPosition(m_TextEdit, 0, Qt::AlignCenter);

    // m_TimeZoneContainer
    m_TimeZoneContainer = new TimeZoneContainer(this);
    QTimer *addTimer = new QTimer(this);
    addTimer->setSingleShot(true);
    connect(addTimer, SIGNAL(timeout()), this, SLOT(addMoreListItems()));
    addTimer->start(0);

    // add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(textEditLayout, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_TimeZoneContainer, 1, Qt::AlignCenter);

    // orientation change
    connect(DuiSceneManager::instance(), SIGNAL(orientationChanged(const Dui::Orientation &)),
            this, SLOT(orientationChanged()));
    orientationChanged();
}

void TimeZoneView::orientationChanged()
{
}

void TimeZoneView::clearTextEdit(DuiTextEdit *textEdit)
{
    if (textEdit->text() == DcpDateTime::InputCountryText) {
        textEdit->setText("");
    }
}

void TimeZoneView::filteringListItems()
{
    QString sample = m_TextEdit->text();
    if (sample == DcpDateTime::InputCountryText)
        sample = "";
    m_TimeZoneContainer->filter(sample);
}

void TimeZoneView::addMoreListItems()
{
    m_TimeZoneContainer->addMoreItems();
}

