#include "dcpbackgroundcomponent.h"

#include <duilinearlayout.h>
#include <duilabel.h>
#include <duitheme.h>
#include "dcpbackgroundlineview.h"

DcpBackgroundComponent::DcpBackgroundComponent(
                            DcpCategory *category,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpComponent(category, title, parent), m_Background(NULL), m_Caption(NULL)
{
    setViewType("bglineview");
}


DcpBackgroundComponent::~DcpBackgroundComponent() {
    // DuiTheme::releasePixmap(m_Background);
}

void DcpBackgroundComponent::resizeEvent ( QGraphicsSceneResizeEvent * event )
{
    DcpBackgroundLineView* view =
            qobject_cast<DcpBackgroundLineView*>(this->view);
    if (view && m_Caption) {
        view->setLinePosition(m_Caption->geometry().bottom() + 2);
    }
    DuiWidgetController::resizeEvent(event);
}

void
DcpBackgroundComponent::createContents()
{
    m_Layout = new DuiLinearLayout(Qt::Vertical);
    m_Caption = new DuiLabel(title());
    m_Caption->setObjectName("ComponentCaption");

    // TODO: move to stylesheet
    this->setContentsMargins(10, 0, 10, 0);
    // --

    // this fixes a dui issue, that the labels are eating up our clickEvents
    m_Caption->setAcceptedMouseButtons(0);
    // --

    setLayout(m_Layout);
    addItem(m_Caption);
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
    m_Layout->addItem(item);
}
