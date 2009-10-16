#include "dcpcategorycomponent.h"
#include "dcpappletbuttons.h"

#include <DuiContainer>
#include <DuiLayout>
#include <DuiLinearLayoutPolicy>
#include <DuiSceneManager>


/*!
 * \class DcpCategoryComponent
 * \brief A component for the recently used applets
 *
 * It is supplies the background and title for around DcpAppletButtons,
 * which contains the buttons. (Actually uses DuiContainer for that.)
 */

DcpCategoryComponent::DcpCategoryComponent(
                            DcpCategory *category,
                            const QString& categoryName,
                            QGraphicsWidget *parent)
        : DcpComponent(category, categoryName, parent),
         m_CategoryName(categoryName)
{
    createContents();
}

DcpCategoryComponent::~DcpCategoryComponent()
{
}

void DcpCategoryComponent::setTitleText(const QString& title)
{
    m_Container->setTitle(title);
}

void DcpCategoryComponent::createContents()
{
    m_Container = new DuiContainer(this);
    m_Container->setSizePolicy(QSizePolicy::Expanding,
                                 QSizePolicy::Expanding);

    m_AppletButtons = new DcpAppletButtons(m_CategoryName, title());

	
    connect(m_AppletButtons, SIGNAL(openSubPage(Pages::Handle)),
            this, SIGNAL(openSubPage(Pages::Handle)));

    m_Container->setCentralWidget(m_AppletButtons);

    DuiLayout* layout = new DuiLayout(this);
    layout->setAnimator(0);
    layout->setContentsMargins(0,0,0,0);
    DuiLinearLayoutPolicy* layoutPolicy = new DuiLinearLayoutPolicy(layout, Qt::Vertical);
    layoutPolicy->addItem(m_Container);
    layout->setPolicy(layoutPolicy);
    connect (DuiSceneManager::instance(),
             SIGNAL(orientationChanged(const Dui::Orientation&)),
             this, SLOT(onOrientationChange(const Dui::Orientation &)));
}

void DcpCategoryComponent::onOrientationChange
                            (const Dui::Orientation &orientation)
{
    m_AppletButtons->onOrientationChange(orientation);
}

void DcpCategoryComponent::reload()
{
    m_AppletButtons->reload();
}

