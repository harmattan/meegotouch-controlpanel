#include "dcpcategorycomponent.h"
#include "dcpappletbuttons.h"

#include <DuiContainer>
#include <QGraphicsLinearLayout>
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

void DcpCategoryComponent::setTitle(const QString& title)
{
    m_Container->setTitle(title);
    DcpComponent::setTitle(title);
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

    QGraphicsLinearLayout* layout =
        new QGraphicsLinearLayout(Qt::Vertical,this);
    layout->addItem(m_Container);
}

void DcpCategoryComponent::reload()
{
    m_AppletButtons->reload();
}

void DcpCategoryComponent::onOrientationChange
                            (const Dui::Orientation &orientation)
{
    m_AppletButtons->onOrientationChange(orientation);
}

