#include "dcpbackgroundcomponent.h"
#include "dcpbackgroundlineview.h"

#include <duilabel.h>
#include <duibutton.h>
#include <duitheme.h>
#include <duilinearlayoutpolicy.h>
#include <duibasiclayoutanimator.h>

DcpBackgroundComponent::DcpBackgroundComponent(
                            DcpCategory *category,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpComponent(category, title, parent),
    m_HasSignButton(true),
    m_Background(NULL),
    m_Caption(NULL)
{
   setViewType("bglineview");
}


void DcpBackgroundComponent::resizeEvent ( QGraphicsSceneResizeEvent * event )
{
    DuiWidgetController::resizeEvent(event);
}


void DcpBackgroundComponent::paint (QPainter *painter,
                                    const QStyleOptionGraphicsItem *option,
                                    QWidget *widget)
{
    DcpBackgroundLineView* view =
            qobject_cast<DcpBackgroundLineView*>(this->view);
    if (view && m_Caption) {
        qreal top;
        getContentsMargins(NULL,&top,NULL,NULL);
        view->setLinePosition(m_Caption->size().height()+top);
    }
    DcpComponent::paint(painter, option, widget);
}

void
DcpBackgroundComponent::createContents()
{
    DuiLayout* layout = new DuiLayout();

    layout->setAnimator(NULL);

    m_Layout = new DuiLinearLayoutPolicy(layout,Qt::Vertical);
    m_Caption = new DuiLabel(title());
    m_Caption->setObjectName("ComponentCaption");

    DuiLayout * captionLayout = new DuiLayout();
    captionLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *captionLayoutPolicy =
        new DuiLinearLayoutPolicy(captionLayout, Qt::Horizontal);
    captionLayout->setPolicy(captionLayoutPolicy);

    captionLayoutPolicy->addItemAtPosition(m_Caption,
                    0, Qt::AlignLeft | Qt::AlignBottom);

    // TODO: move to stylesheet
    this->setContentsMargins(20, 10, 20, 10);

    /* TODO manni
       remove this way of "parameter passing" after the layout is able to
       handle hidden widgets */
    if (m_HasSignButton) {
        DuiButton* signButton = new DuiButton(this);
        signButton->setObjectName("SignButton");
        signButton->setMaximumWidth(32);
        signButton->setMaximumHeight(32);
        captionLayoutPolicy->addItemAtPosition(signButton,
                        1, Qt::AlignRight | Qt::AlignVCenter);
        this->setContentsMargins(20, 10, 8, 10);
    }

    // this fixes a dui issue, that the labels are eating up our clickEvents
    m_Caption->setAcceptedMouseButtons(0);
    // --

    layout->setPolicy(m_Layout);
    addItem(captionLayout);
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
