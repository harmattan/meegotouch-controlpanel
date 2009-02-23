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
