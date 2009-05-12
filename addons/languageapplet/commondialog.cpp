#include "commondialog.h"
#include "dcpspaceritem.h"

#include <duicontainer.h>
#include <duilabel.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duipannableviewport.h>
#include <duiscenemanager.h>
#include <duiseparator.h>

CommonDialog::CommonDialog(const QString &text)
             :DcpDialog(),
              m_TitleText(text)
{
    initDialog();
}

CommonDialog::~CommonDialog()
{
}

void CommonDialog::setCentralWidget(DuiWidget *widget)
{
    if (m_ContainerLayout->count() > 2) {
        m_ContainerLayout->removeAt(2);
    }
    m_ContainerLayoutPolicy->addItemAtPosition(widget, 2, Qt::AlignCenter);
}

DuiWidget* CommonDialog::centralWidget()
{
    if (m_ContainerLayout->count() > 2) {
        return static_cast<DuiWidget*>(m_ContainerLayout->itemAt(2));
    } else {
        return NULL;
    }
}

void CommonDialog::initDialog()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
        new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    this->setLayout(mainLayout);
    setContentsMargins(0.0, 0.0, 0.0, 0.0);
    mainLayoutPolicy->setSpacing(10);

    // m_Viewport 
    m_Viewport = new DuiPannableViewport(this);
    m_Viewport->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    // m_MainWidget
    m_MainWidget = new DuiContainer(this);
    // m_MainWidget->layout()->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    m_MainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_MainWidget->setHeaderVisible(false);
    m_MainWidget->setExpand(true);
    
    // containerWidget
    DuiWidget *containerWidget = new DuiWidget(m_MainWidget);
    m_ContainerLayout = new DuiLayout(containerWidget);
    m_ContainerLayout->setAnimator(NULL);
    containerWidget->setLayout(m_ContainerLayout);
    m_ContainerLayoutPolicy =
        new DuiLinearLayoutPolicy(m_ContainerLayout, Qt::Vertical);
    m_ContainerLayout->setPolicy(m_ContainerLayoutPolicy);
    m_ContainerLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);

    // titleLayout
    DuiLayout *titleLayout = new DuiLayout(NULL);
    titleLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *titleLayoutPolicy =
        new DuiLinearLayoutPolicy(titleLayout, Qt::Horizontal);
    titleLayout->setPolicy(titleLayoutPolicy);
    titleLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    
    // titleLabel
    DuiLabel *titleLabel = new DuiLabel(m_TitleText, containerWidget);
    titleLabel->setObjectName("CommonDialogTitleLabel");
    titleLabel->setAcceptedMouseButtons(0);

    // greySeparator
    m_GreySeparator = new DuiSeparator(this);
    m_GreySeparator->setObjectName("GreySeparator");
    m_GreySeparator->setAcceptedMouseButtons(0);
    
    // Add items to titleLayoutPolicy
    titleLayoutPolicy->addItemAtPosition(
        new DcpSpacerItem(containerWidget, 5, 5,
        QSizePolicy::Expanding, QSizePolicy::Fixed),
        0, Qt::AlignLeft);
    titleLayoutPolicy->addItemAtPosition(titleLabel, 1, Qt::AlignCenter);
    titleLayoutPolicy->addItemAtPosition(
                        new DcpSpacerItem(containerWidget, 5, 5,
                        QSizePolicy::Expanding, QSizePolicy::Fixed),
                        2, Qt::AlignRight);

    // Add items to m_ContainerLayoutPolicy
    m_ContainerLayoutPolicy->addItemAtPosition(titleLayout, 0, Qt::AlignCenter);
    m_ContainerLayoutPolicy->addItemAtPosition(m_GreySeparator, 1, Qt::AlignCenter);

    // Add viewport to DuiContainer
    m_MainWidget->setCentralWidget(containerWidget);
    m_Viewport->setWidget(m_MainWidget);

    // Add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding),
            0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_Viewport, 1, Qt::AlignCenter);

    // orientation
    connect(DuiSceneManager::instance(), SIGNAL(orientationChanged(const Dui::Orientation &)),
            this, SLOT(onOrientationAngleChanged ()));
    onOrientationAngleChanged();
}

void CommonDialog::onOrientationAngleChanged()
{
    QSizeF dialogSize = DuiSceneManager::instance()->visibleSceneRect();
    dialogSize.setHeight(dialogSize.height() - 90);
    m_Viewport->setMinimumSize(dialogSize);
    m_Viewport->setMaximumSize(dialogSize);
}
