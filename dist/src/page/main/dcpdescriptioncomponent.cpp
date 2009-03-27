#include "dcpdescriptioncomponent.h"

#include <QtDebug>
#include <QGraphicsSceneResizeEvent>

#include <duilabel.h>

#include <duigridlayout.h>

static const QSize fullSizeLandscape(784,90);
static const QSize halfSizeLandscape(372,90);
static const QSize fullSizePortrait = fullSizeLandscape;
static const QSize halfSizePortrait = fullSizeLandscape;

DcpDescriptionComponent::DcpDescriptionComponent(DcpCategory *category,
                                                 const QString& title,
                                                 QGraphicsWidget *parent) :
    DcpBackgroundComponent(category, title, parent),
    m_Orientation(Dui::Landscape)
{
    createContents();
}


void
DcpDescriptionComponent::createContents()
{
    DcpBackgroundComponent::createContents();

    m_Description = new DuiLabel();
    m_Description->setObjectName("ComponentDescription");
    m_Description->setWordWrap(true);

    setHalfRowSize();

    // this fixes a dui issue, that the labels are eating up our clickEvents
    m_Description->setAcceptedMouseButtons(0);
    // --

    addItem(m_Description);
}


void DcpDescriptionComponent::onOrientationChange (
                                        const Dui::Orientation &orientation)
{
    m_Orientation = orientation;
    DcpBackgroundComponent::onOrientationChange(orientation);
/*    if (m_IsFullRow || orientation == Dui::Portrait) {
        setFullRowSize();
    } else {
        setHalfRowSize();
    } */
}


void DcpDescriptionComponent::setDescription(const QString& desc)
{
    m_Description->setText(desc);
}


void DcpDescriptionComponent::setTextAlignment(Qt::Alignment align)
{
    m_Description->setAlignment(align);
}


/** This function changes the component's look and feel to the one
  * that is the full row size description.
  */
void DcpDescriptionComponent::setFullRowSize()
{
    /* prohibit the description to change the widget's width too big */
    // TODO: move to stylesheet
    QSize fullSize = (m_Orientation != Dui::Portrait) ? fullSizeLandscape
                     : fullSizePortrait;
    m_Description->setMaximumSize(fullSize);
    m_Description->setMinimumSize(fullSize);
    // --

    setTextAlignment(Qt::AlignHCenter);
    setTitleAlignment(Qt::AlignHCenter);
    m_IsFullRow = true;
}


void DcpDescriptionComponent::setHalfRowSize()
{
    /* prohibit the description to change the widget's width too big */
    // TODO: move to stylesheet
    QSize halfSize = (m_Orientation != Dui::Portrait) ? halfSizeLandscape
                     : halfSizePortrait;
    m_Description->setMaximumSize(halfSize);
    m_Description->setMinimumSize(halfSize);
    // --

    setTextAlignment(Qt::AlignTop);
    setTitleAlignment(Qt::AlignLeft);
    m_IsFullRow = false;
}


void DcpDescriptionComponent::mousePressEvent (QGraphicsSceneMouseEvent *event)
{
    DcpBackgroundComponent::mousePressEvent(event);
    event->accept();
    switchToSubPage();
}

void DcpDescriptionComponent::mouseReleaseEvent (QGraphicsSceneMouseEvent * event)
{
    DcpBackgroundComponent::mouseReleaseEvent(event);
    event->accept();
}

void DcpDescriptionComponent::polishEvent (){
    /* TODO remove this workaround once DuiLabel's word wrap is corrected
     * for html.
     * It forces the description to rethink the word wraps correctly */
    
    static qreal change = 0.0001;
    m_Description->setMinimumWidth(m_Description->minimumWidth()-change);
    m_Description->setMaximumWidth(m_Description->maximumWidth()-change);
    m_Description->setText(m_Description->text());

    /* --- */

    DcpBackgroundComponent::polishEvent();
}
