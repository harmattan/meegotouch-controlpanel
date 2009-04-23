#include "dcpdescriptioncomponent.h"

#include <QtDebug>
#include <QGraphicsSceneResizeEvent>

#include <duilabel.h>

static const QSize fullSizeLandscape(804,90);
static const QSize halfSizeLandscape(385,90);
static const QSize halfSizePortrait(429,90);
static const QSize fullSizePortrait = halfSizePortrait;

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
    initSizes();
    DcpBackgroundComponent::onOrientationChange(orientation);
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
    m_IsFullRow = true;
}


void DcpDescriptionComponent::initSizes()
{
	QSize descSize;
	if (m_IsFullRow) {
	    descSize = (m_Orientation != Dui::Portrait) ? fullSizeLandscape
			     : fullSizePortrait;

	    setTextAlignment(Qt::AlignHCenter);
	    setTitleAlignment(Qt::AlignHCenter);
	} else {
    	    descSize = (m_Orientation != Dui::Portrait) ? halfSizeLandscape
                     	     : halfSizePortrait;
    	    setTextAlignment(Qt::AlignTop);
    	    setTitleAlignment(Qt::AlignLeft);
	}
	m_Description->setMaximumSize(descSize);
	m_Description->setMinimumSize(descSize);
}


void DcpDescriptionComponent::setHalfRowSize()
{
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


