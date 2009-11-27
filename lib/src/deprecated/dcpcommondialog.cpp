#include "dcpcommondialog.h"
#include "dcpspaceritem.h"

#include <duicontainer.h>
#include <duilabel.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duipannableviewport.h>
#include <duiscenemanager.h>
#include <duiseparator.h>
#include <duibutton.h>

DcpCommonDialog::DcpCommonDialog(const QString &text, DuiWidget* parent)
             :DcpDialog(parent)
{
    setObjectName("DcpCommonDialog");
    initDialog();
    setTitle(text);
}

DcpCommonDialog::~DcpCommonDialog()
{
}

void DcpCommonDialog::setCentralWidget(DuiWidget *widget)
{
    if (m_ContainerLayout->count() > 2) {
        m_ContainerLayout->removeAt(2);
    }
//    m_ContainerLayoutPolicy->insertItem(widget, 2, Qt::AlignCenter); TODO for dui >0.11
    m_ContainerLayoutPolicy->addItemAtPosition(widget, 2, Qt::AlignCenter);
}

DuiWidget* DcpCommonDialog::centralWidget()
{
    if (m_ContainerLayout->count() > 2) {
        return static_cast<DuiWidget*>(m_ContainerLayout->itemAt(2));
    } else {
        return 0;
    }
}

void DcpCommonDialog::initDialog()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
    this->setLayout(mainLayout);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
        new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    mainLayoutPolicy->setSpacing(10);

    // FIXME -- backbutton temporary solution until it is getting possible
    // in libdui to do not cover the backbutton with the scenelayereffect
    DuiButton* backButton = new DuiButton(this);
    backButton->setViewType("icon");
    backButton->setIconID("Icon-back");
    backButton->setObjectName("NavigationBarBackButton");
    connect (backButton, SIGNAL(clicked()), this, SLOT(accept()));

    DuiLayout* backButtonLayout = new DuiLayout(0);
    backButtonLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    backButtonLayout->setAnimator(0);
    DuiLinearLayoutPolicy* backButtonLayoutPolicy = new DuiLinearLayoutPolicy(backButtonLayout,
            Qt::Horizontal);
    backButtonLayoutPolicy->addItem(
            new DcpSpacerItem(this, 10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding),
            Qt::AlignLeft);
    backButtonLayoutPolicy->addItem(backButton, Qt::AlignRight | Qt::AlignTop);
    // -- FIXME ends

    // m_Viewport
    m_Viewport = new DuiPannableViewport(this);
    m_Viewport->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // m_MainWidget
    m_MainWidget = new DuiContainer(0);
    m_MainWidget->setObjectName("DcpCommonDialogContainer");
    m_MainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_MainWidget->setHeaderVisible(false);

    // FIXME temporary workaround for setHeaderVisible not working (layout bug?)
    delete m_MainWidget->layout()->itemAt(0);
    delete m_MainWidget->layout()->itemAt(0);

    m_MainWidget->setExpand(true);

    // containerWidget
    DuiWidget *containerWidget = new DuiWidget(m_MainWidget);
    m_ContainerLayout = new DuiLayout(containerWidget);
    m_ContainerLayout->setAnimator(0);
    containerWidget->setLayout(m_ContainerLayout);
    m_ContainerLayoutPolicy =
        new DuiLinearLayoutPolicy(m_ContainerLayout, Qt::Vertical);
    m_ContainerLayout->setPolicy(m_ContainerLayoutPolicy);
    m_ContainerLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    m_ContainerLayoutPolicy->setSpacing(10);

    // titleLayout
    DuiLayout *titleLayout = new DuiLayout(0);
    titleLayout->setAnimator(0);
    DuiLinearLayoutPolicy *titleLayoutPolicy =
        new DuiLinearLayoutPolicy(titleLayout, Qt::Horizontal);
    titleLayout->setPolicy(titleLayoutPolicy);
    titleLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);

    // m_TitleLabel
    m_TitleLabel = new DuiLabel(containerWidget);
    m_TitleLabel->setObjectName("DcpCommonDialogTitleLabel");
    m_TitleLabel->setAcceptedMouseButtons(0);

    // greySeparator
    m_GreySeparator = new DuiSeparator(containerWidget);
    m_GreySeparator->setAcceptedMouseButtons(0);

    // Add items to titleLayoutPolicy
    titleLayoutPolicy->addItem(
        new DcpSpacerItem(containerWidget, 5, 5,
        QSizePolicy::Expanding, QSizePolicy::Fixed),
        Qt::AlignLeft);
    titleLayoutPolicy->addItem(m_TitleLabel, Qt::AlignCenter);
    titleLayoutPolicy->addItem(
                        new DcpSpacerItem(containerWidget, 5, 5,
                        QSizePolicy::Expanding, QSizePolicy::Fixed),
                        Qt::AlignRight);

    // Add items to m_ContainerLayoutPolicy
    m_ContainerLayoutPolicy->addItem(titleLayout, Qt::AlignCenter);
    m_ContainerLayoutPolicy->addItem(m_GreySeparator, Qt::AlignCenter);

    // Add viewport to DuiContainer
    m_MainWidget->setCentralWidget(containerWidget);
    m_Viewport->setWidget(m_MainWidget);

    // Add items to mainLayoutPolicy
    mainLayoutPolicy->addItem(backButtonLayout);
    mainLayoutPolicy->addItem(m_Viewport, Qt::AlignCenter);
}

void DcpCommonDialog::setTitle(const QString& title)
{
    m_TitleLabel->setText(title);
}
