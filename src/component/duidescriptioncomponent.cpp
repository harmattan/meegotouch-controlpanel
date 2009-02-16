#include "duidescriptioncomponent.h"


#include <duilinearlayout.h>
#include <duilabel.h>


DuiDescriptionComponent::DuiDescriptionComponent(DuiSettingsCategory *category,
                                                 const QString& title,
                                                 QGraphicsWidget *parent) :
    DuiSettingsComponent(category, title, parent)
{
    createContents();
}


void
DuiDescriptionComponent::createContents()
{
    m_Layout = new DuiLinearLayout(Qt::Vertical);
    m_Caption = new DuiLabel(title());
    m_Description = new DuiLabel();
    m_Description->setWordWrap(true);
    m_Description->setMaximumWidth(400);
    m_Layout->addItem(m_Caption);
    m_Layout->addItem(m_Description);
    setLayout(m_Layout);
}


void
DuiDescriptionComponent::onOrientationChange (const Dui::Orientation &orientation)
{
    Q_UNUSED(orientation);
}


void DuiDescriptionComponent::setTitle(const QString& title){
    m_Caption->setText(title);
    DuiSettingsComponent::setTitle(title);
}


void DuiDescriptionComponent::setDescription(const QString& desc){
    m_Description->setText(desc);
}

