#include "dcpdescriptioncomponent.h"

#include <duilabel.h>
#include <duicontainer.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>

#include <QGraphicsSceneMouseEvent>

/*!
 * \class DcpDescriptionComponent
 * \brief DcpDescriptionComponent is a DcpComponent which is meant for
 * the main screen to providethe button that describes an an applet category.
 *
 * It displays a title and description about the category, and requests
 * the page switching if the user clicked on it.
 * Currently uses DuiContainer for all rendering stuff. */

DcpDescriptionComponent::DcpDescriptionComponent(DcpCategory *category,
                                                 const QString& title,
                                                 QGraphicsWidget *parent) :
    DcpComponent(category, title, parent),
    m_Container(NULL)
{
    createContents();
}


void
DcpDescriptionComponent::createContents()
{
    m_Container = new DuiContainer(this);
    m_Container->setAcceptedMouseButtons(0);
/*    m_Container->setSizePolicy(QSizePolicy::Expanding,
                                 QSizePolicy::Expanding);*/
    setTitle(title());

//    m_Container->setText("More...");
//     m_Container->setExpand(true);
//     m_Container->setIconID("My-Icon-ID");

    m_Description = new DuiLabel(m_Container);
    m_Description->setObjectName("ComponentDescription");
    m_Description->setWordWrap(true);
    m_Description->setAcceptedMouseButtons(0);
    m_Description->setSizePolicy(QSizePolicy::Expanding,
                                 QSizePolicy::Expanding);

    m_Container->setCentralWidget(m_Description);

    DuiLayout* layout = new DuiLayout(this);
    layout->setAnimator(NULL);
    layout->setContentsMargins(0,0,0,0);
    DuiLinearLayoutPolicy* layoutPolicy = new DuiLinearLayoutPolicy(layout,
                                                            Qt::Vertical);
    layoutPolicy->addItemAtPosition(m_Container, 0);
    layout->setPolicy(layoutPolicy);
}

void DcpDescriptionComponent::setTitle (const QString& title)
{
    Q_ASSERT(m_Container);
    m_Container->setTitle(title);
    DcpComponent::setTitle(title);
}


void DcpDescriptionComponent::setDescription(const QString& desc)
{
    m_Description->setText(desc);
}


void DcpDescriptionComponent::setTextAlignment(Qt::Alignment align)
{
    m_Description->setAlignment(align);
}


void DcpDescriptionComponent::mousePressEvent (QGraphicsSceneMouseEvent *event)
{
    DcpComponent::mousePressEvent(event);
    event->accept();
    switchToSubPage();
}


void DcpDescriptionComponent::mouseReleaseEvent (QGraphicsSceneMouseEvent * event)
{
    DcpComponent::mouseReleaseEvent(event);
    event->accept();
}


