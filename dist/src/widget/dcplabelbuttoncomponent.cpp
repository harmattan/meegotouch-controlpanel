#include "dcplabelbuttoncomponent.h"
#include "dcpappletmetadata.h"


DcpLabelButtonComponent::DcpLabelButtonComponent(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpBasicComponent(category, metadata, title, parent)
{
    createContents();
}


DcpLabelButtonComponent::~DcpLabelButtonComponent()
{
}


void DcpLabelButtonComponent::createContents()
{

}
