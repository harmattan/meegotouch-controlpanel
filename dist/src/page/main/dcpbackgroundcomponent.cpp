#include "dcpbackgroundcomponent.h"
#include "dcpbackgroundlineview.h"

#include <duilabel.h>
#include <duitheme.h>
#include <duilinearlayoutpolicy.h>
#include <duibasiclayoutanimator.h>

DcpBackgroundComponent::DcpBackgroundComponent(
                            DcpCategory *category,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpComponent(category, title, parent), m_Background(NULL), m_Caption(NULL)
{
    setViewType("bglineview");
}


void DcpBackgroundComponent::resizeEvent ( QGraphicsSceneResizeEvent * event )
{
    DcpBackgroundLineView* view =
            qobject_cast<DcpBackgroundLineView*>(this->view);
    if (view && m_Caption) {
        qreal top;
        getContentsMargins(NULL,&top,NULL,NULL);
        view->setLinePosition(m_Caption->size().height()+top);
    }
    DuiWidgetController::resizeEvent(event);
}

void
DcpBackgroundComponent::createContents()
{
    DuiLayout* layout = new DuiLayout();

    //    layout->setAnimator(NULL);
    DuiBasicLayoutAnimator* animator = new DuiBasicLayoutAnimator();
    animator->setAnimationSpeed(150);
    layout->setAnimator(animator);

    m_Layout = new DuiLinearLayoutPolicy(layout,Qt::Vertical);
    m_Caption = new DuiLabel(title());
    m_Caption->setObjectName("ComponentCaption");

    // TODO: move to stylesheet
    this->setContentsMargins(20, 10, 20, 10);
    // --

    // this fixes a dui issue, that the labels are eating up our clickEvents
    m_Caption->setAcceptedMouseButtons(0);
    // --

    addItem(m_Caption);
    layout->setPolicy(m_Layout);
    setLayout(layout);
}


void DcpBackgroundComponent::setTitle(const QString& title)
{
    m_Caption->setText(title);
    DcpComponent::setTitle(title);
}


void DcpBackgroundComponent::setTitleAlignment(Qt::Alignment align)
{
    m_Caption->setAlignment(align);
}


void DcpBackgroundComponent::addItem ( QGraphicsLayoutItem * item )
{
    m_Layout->addItemAtPosition(item, m_Layout->count());
}
