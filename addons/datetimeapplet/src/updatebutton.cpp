#include "updatebutton.h"
#include "dcpspaceritem.h"
#include "datetimetranslation.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duigridlayoutpolicy.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duiscenemanager.h>

int height = 88;

UpdateButton::UpdateButton(DuiWidget *parent)
             :DuiWidget(parent)
{
    initWidget();
}

UpdateButton::~UpdateButton()
{
}

void UpdateButton::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
    mainLayout->setContentsMargins(12.0, 0.0, 12.0, 0.0);
    this->setLayout(mainLayout);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
        new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setSpacing(10);

    // lineLayout
    DuiLayout *lineLayout = new DuiLayout(0);
    lineLayout->setAnimator(0);
    lineLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    DuiGridLayoutPolicy *lineLayoutPolicy = new DuiGridLayoutPolicy(lineLayout);
    lineLayout->setPolicy(lineLayoutPolicy);
    lineLayoutPolicy->setSpacing(5);

    // automaticLabel
    m_AutomaticLabel = new DuiLabel(DcpDateTime::AutomaticUpdateText, this);
    m_AutomaticLabel->setObjectName("AutomaticLabel");
    m_AutomaticLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_AutomaticLabel->setAcceptedMouseButtons(0);
    
    // toggleButton
    DuiButton *toggleButton = new DuiButton(this);
    toggleButton->setObjectName("ToggleButton");
    toggleButton->setCheckable(true);
    toggleButton->setTextVisible(false);
    
    // add items to lineLayoutPolicy
    lineLayoutPolicy->addItemAtPosition(m_AutomaticLabel, 0, 0);
    lineLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding),
            0, 1);
    lineLayoutPolicy->addItemAtPosition(toggleButton, 0, 2);

    // add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Fixed, QSizePolicy::Expanding),
            0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(lineLayout, 1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Fixed, QSizePolicy::Expanding),
            2, Qt::AlignCenter);

    // set fixed height
    this->setMinimumHeight(height);
    this->setMaximumHeight(height);

    connect(DuiSceneManager::instance(), SIGNAL(orientationChanged(const Dui::Orientation &)),
            this, SLOT(onOrientationChanged()));
    onOrientationChanged();
}

void UpdateButton::onOrientationChanged()
{
    DuiSceneManager* manager = DuiSceneManager::instance();
    if (manager == 0) return;

    switch (manager->orientation()) {
        case Dui::Landscape:
            this->setMinimumWidth(manager->visibleSceneSize().width() - 30);
            this->setMaximumWidth(manager->visibleSceneSize().width() - 30);
            m_AutomaticLabel->setMinimumWidth(
                DuiSceneManager::instance()->visibleSceneSize().width() - 130);
            break;
        case Dui::Portrait:
            this->setMinimumWidth(manager->visibleSceneSize().width() - 30);
            this->setMaximumWidth(manager->visibleSceneSize().width() - 30);
            m_AutomaticLabel->setMinimumWidth(
                DuiSceneManager::instance()->visibleSceneSize().width() - 130);
            break;
        default:
            break;
    }
}

