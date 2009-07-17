#include "updatebutton.h"
#include "dcpspaceritem.h"
#include "datetimetranslation.h"

#include <duigridlayoutpolicy.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duiscenemanager.h>
#include <QGraphicsLinearLayout>

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
    QGraphicsLinearLayout *mainLayout = new QGraphicsLinearLayout(Qt::Horizontal, this);
    mainLayout->setContentsMargins(12.0, 15.0, 12.0, 15.0);
    mainLayout->setSpacing(10);

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
    
    // add items to mainlayout
    mainLayout->addItem(m_AutomaticLabel);
    mainLayout->setAlignment(m_AutomaticLabel, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addItem(new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Fixed));
    mainLayout->addItem(toggleButton);
    mainLayout->setAlignment(toggleButton, Qt::AlignRight | Qt::AlignVCenter);

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
            break;
        case Dui::Portrait:
            this->setMinimumWidth(manager->visibleSceneSize().width() - 30);
            this->setMaximumWidth(manager->visibleSceneSize().width() - 30);
            break;
        default:
            break;
    }
}

