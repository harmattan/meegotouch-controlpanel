#include "commondialog.h"
#include "dcpspaceritem.h"

#include <duicontainer.h>
#include <duilabel.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duipannableviewport.h>

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
    if (m_ContainerLayout->count() > 1) {
        m_ContainerLayout->removeAt(1);
    }

    m_ContainerLayoutPolicy->addItemAtPosition(widget, 1, Qt::AlignCenter);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

DuiWidget* CommonDialog::centralWidget()
{
    if (m_ContainerLayout->count() > 1) {
        return static_cast<DuiWidget*>(m_ContainerLayout->itemAt(1));
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
    setContentsMargins(15.0, 20.0, 20.0, 15.0);
    mainLayoutPolicy->setSpacing(1);
    
    // m_MainWidget
    m_MainWidget = new DuiContainer(this);
    m_MainWidget->layout()->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    m_MainWidget->setHeaderVisible(false);
    m_MainWidget->setExpand(true);
    mainLayoutPolicy->addItemAtPosition(m_MainWidget, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 10, 10, QSizePolicy::Expanding, QSizePolicy::Fixed),
            1, Qt::AlignCenter);

    // containerWidget
    DuiWidget *containerWidget = new DuiWidget(m_MainWidget);
    m_ContainerLayout = new DuiLayout(containerWidget);
    m_ContainerLayout->setAnimator(NULL);
    m_ContainerLayoutPolicy =
        new DuiLinearLayoutPolicy(m_ContainerLayout, Qt::Vertical);
    m_ContainerLayout->setPolicy(m_ContainerLayoutPolicy);
    containerWidget->setLayout(m_ContainerLayout);

    // titleLayout
    DuiLayout *titleLayout = new DuiLayout(NULL);
    titleLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *titleLayoutPolicy =
        new DuiLinearLayoutPolicy(titleLayout, Qt::Horizontal);
    titleLayout->setPolicy(titleLayoutPolicy);
    
    // titleLabel
    DuiLabel *titleLabel = new DuiLabel(m_TitleText, containerWidget);
    titleLabel->setObjectName("CommonDialogTitleLabel");
    titleLabel->setAcceptedMouseButtons(0);
    
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

    // pannable viewport
    DuiPannableViewport* viewport = new DuiPannableViewport(m_MainWidget);
    viewport->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    viewport->setWidget(containerWidget);
    
    // Add viewport to DuiContainer
    m_MainWidget->setCentralWidget(viewport);

    // orientation
    connect(DuiDeviceProfile::instance(), SIGNAL(orientationAngleChanged (DuiDeviceProfile::DeviceOrientationAngle)),
            this, SLOT(onOrientationAngleChanged ()));
    onOrientationAngleChanged();
}

void CommonDialog::onOrientationAngleChanged()
{
    QSizeF dialogSize = DuiDeviceProfile::instance()->resolution();
    dialogSize.setHeight(dialogSize.height() - 100);
    dialogSize.setWidth(dialogSize.width() - 30);
    layout()->itemAt(0)->setMinimumSize(dialogSize);
    layout()->itemAt(0)->setMaximumSize(dialogSize);
}
