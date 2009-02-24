#include "dcpsimplecomponent.h" 
#include <QtDebug>
DcpSimpleComponent::DcpSimpleComponent(DcpCategory *category,
                                  const QString& title, 
				  QGraphicsWidget *parent) :
		 DcpComponent(category, title, parent)
{
   createContents();
}	 

void
DcpSimpleComponent::createContents()
{}
    
void
DcpSimpleComponent::add(DcpComponent *component)
{
    Q_UNUSED(component)
}

void
DcpSimpleComponent::remove(DcpComponent *component)
{
    Q_UNUSED(component)
}
