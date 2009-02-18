#include "duidescriptioncomponent.h"

#include <QtDebug>
#include <QGraphicsSceneResizeEvent>

#include <duilabel.h>

static const QSize fullSize(720,65);
static const QSize halfSize(340,65);

DuiDescriptionComponent::DuiDescriptionComponent(DuiSettingsCategory *category,
                                                 const QString& title,
                                                 QGraphicsWidget *parent) :
    DuiBackgroundComponent(category, title, parent)
{
    createContents();
}


void
DuiDescriptionComponent::createContents()
{
    DuiBackgroundComponent::createContents();

    m_Description = new DuiLabel();
    m_Description->setObjectName("ComponentDescription");
    m_Description->setAlignment(Qt::AlignJustify | Qt::AlignTop);
    m_Description->setWordWrap(true);

    // TODO: move to stylesheet
    m_Description->setMaximumSize(halfSize);
    m_Description->setMinimumSize(halfSize);
    // --

    // this fixes a dui issue, that the labels are eating up our clickEvents
    m_Description->setAcceptedMouseButtons(0);
    // --

    addItem(m_Description);
}


void
DuiDescriptionComponent::onOrientationChange (const Dui::Orientation &orientation)
{
    DuiBackgroundComponent::onOrientationChange(orientation);
}


void DuiDescriptionComponent::setDescription(const QString& desc)
{
    m_Description->setText(desc);
}


void DuiDescriptionComponent::setTextAlignment(Qt::Alignment align)
{
    m_Description->setAlignment(align);
}


/** This function changes the component's look and feel to the one
  * that is the full row size description.
  */
void DuiDescriptionComponent::setFullRowSize()
{
    /* prohibit the description to change the widget's width too big */
    m_Description->setMaximumSize(fullSize);
    m_Description->setMinimumSize(fullSize);

    setTextAlignment(Qt::AlignHCenter);
    setTitleAlignment(Qt::AlignHCenter);
}


void DuiDescriptionComponent::mousePressEvent (QGraphicsSceneMouseEvent *event)
{
    switchToSubPage();
    DuiBackgroundComponent::mousePressEvent(event);
    event->accept();
}

void DuiDescriptionComponent::mouseReleaseEvent (QGraphicsSceneMouseEvent * event)
{
    DuiBackgroundComponent::mouseReleaseEvent(event);
    event->accept();
}

void DuiDescriptionComponent::polishEvent (){
    /* TODO remove this workaround once DuiLabel's word wrap is corrected
     * for html.
     * It forces the description to rethink the word wraps correctly */
    static qreal change = 0.0001;
    m_Description->setMinimumWidth(m_Description->minimumWidth()-change);
    m_Description->setMaximumWidth(m_Description->maximumWidth()-change);
    m_Description->setText(m_Description->text());
    /* --- */

    DuiBackgroundComponent::polishEvent();
}
