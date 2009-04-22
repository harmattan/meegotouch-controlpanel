#include "dcpdescriptioncomponent.h"

#include <QtDebug>
#include <QGraphicsSceneResizeEvent>

#include <duilabel.h>
#include <duibutton.h>
#include <duicontainer.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>

static const QSize fullSizeLandscape(804,90);
static const QSize halfSizeLandscape(385,90);
static const QSize halfSizePortrait(429,90);
static const QSize fullSizePortrait = halfSizePortrait;

DcpDescriptionComponent::DcpDescriptionComponent(DcpCategory *category,
                                                 const QString& title,
                                                 QGraphicsWidget *parent) :
    DcpComponent(category, title, parent),
    m_Orientation(Dui::Landscape)
{
    createContents();
}


void
DcpDescriptionComponent::createContents()
{
     DuiContainer *box = new DuiContainer(this);

     box->setTitle(title());
     box->setText("More...");
//     box->setExpand(true);
//     box->setIconID("My-Icon-ID");
/*
     DuiButton *button = new DuiButton("Hello container");
     connect (button, SIGNAL(clicked()), box, SLOT(toggleExpand()));
*/

    m_Description = new DuiLabel();
    m_Description->setObjectName("ComponentDescription");
    m_Description->setWordWrap(true);
//    m_Description->setContentsMargins(50,0,50,0);
    setHalfRowSize();

    // this fixes a dui issue, that the labels are eating up our clickEvents
    m_Description->setAcceptedMouseButtons(0);
    box->setAcceptedMouseButtons(0);
    // --

    box->setCentralWidget(m_Description);
 //   box->setCentralWidget(button);

    DuiLayout* layout = new DuiLayout(this);
    layout->setAnimator(NULL);
    DuiLinearLayoutPolicy* layoutPolicy = new DuiLinearLayoutPolicy(layout,
                                                            Qt::Vertical);
    layoutPolicy->addItemAtPosition(box, 0);
    layout->setPolicy(layoutPolicy);
}


void DcpDescriptionComponent::onOrientationChange (
                                        const Dui::Orientation &orientation)
{
    m_Orientation = orientation;
    initSizes();
    DcpComponent::onOrientationChange(orientation);
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
	    //setTitleAlignment(Qt::AlignHCenter);
	} else {
    	    descSize = (m_Orientation != Dui::Portrait) ? halfSizeLandscape
                     	     : halfSizePortrait;
    	    setTextAlignment(Qt::AlignTop);
    	    //setTitleAlignment(Qt::AlignLeft);
	}
//	m_Description->setMaximumSize(descSize);
//	m_Description->setMinimumSize(descSize);
}


void DcpDescriptionComponent::setHalfRowSize()
{
    m_IsFullRow = false;
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


