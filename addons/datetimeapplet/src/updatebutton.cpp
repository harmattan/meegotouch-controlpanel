#include "updatebutton.h"
#include "dcpspaceritem.h"
#include "datetimetranslation.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duigridlayoutpolicy.h>
#include <duilabel.h>
#include <duiseparator.h>
#include <duiscenemanager.h>

int height = 88;

UpdateButton::UpdateButton(DuiWidget *parent)
             :DuiButton(parent)
{
    initWidget();
}

UpdateButton::~UpdateButton()
{
}

void UpdateButton::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void UpdateButton::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
    mainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    this->setLayout(mainLayout);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
        new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);

    // lineLayout
    DuiLayout *lineLayout = new DuiLayout(0);
    lineLayout->setAnimator(0);
    lineLayout->setContentsMargins(20.0, 0.0, 20.0, 0.0);
    DuiLinearLayoutPolicy *lineLayoutPolicy =
        new DuiLinearLayoutPolicy(lineLayout, Qt::Horizontal);
    lineLayout->setPolicy(lineLayoutPolicy);

    // automaticLabel
    DuiLabel *automaticLabel = new DuiLabel(DcpDateTime::AutomaticUpdateText, this);
    automaticLabel->setObjectName("AutomaticLabel");
    automaticLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    automaticLabel->setAcceptedMouseButtons(0);

    // toggleButton
    DuiButton *toggleButton = new DuiButton(this);
    toggleButton->setObjectName("ToggleButton");
    toggleButton->setMinimumSize(QSize(48, 48));
    toggleButton->setMaximumSize(QSize(48, 48));
    toggleButton->setCheckable(true);
    
    // add items to lineLayoutPolicy
    lineLayoutPolicy->addItemAtPosition(automaticLabel, 0, Qt::AlignRight | Qt::AlignVCenter);
    lineLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Fixed),
            1, Qt::AlignCenter);
    lineLayoutPolicy->addItemAtPosition(toggleButton, 2, Qt::AlignRight | Qt::AlignVCenter);

    // graySeparator
    DuiSeparator *graySeparator = new DuiSeparator(this);
    graySeparator->setObjectName("GraySeparator");
    graySeparator->setMinimumWidth(DuiSceneManager::instance()->visibleSceneRect().width() - 30);
    graySeparator->setMaximumWidth(DuiSceneManager::instance()->visibleSceneRect().width() - 30);

    // add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Fixed, QSizePolicy::Expanding),
            0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(lineLayout, 1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Fixed, QSizePolicy::Expanding),
            2, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(graySeparator, 3, Qt::AlignCenter);

    // set fixed height
    this->setMinimumHeight(height);
    this->setMaximumHeight(height);
}
