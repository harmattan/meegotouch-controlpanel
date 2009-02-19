#include "duisimplecomponent.h" 
#include <QtDebug>
DuiSimpleComponent::DuiSimpleComponent(DuiSettingsCategory *category,
                                  const QString& title, 
				  QGraphicsWidget *parent) :
		 DuiSettingsComponent(category, title, parent)
{
   createContents();
}	 

void
DuiSimpleComponent::createContents()
{}
