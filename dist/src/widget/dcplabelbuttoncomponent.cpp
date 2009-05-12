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
	m_Button = new DcpButton(DCPLABEL2, "", this);

	m_Button->setText(metadata()->text1(), metadata()->text2());
   	m_WidgetLayoutPolicy->addItemAtPosition(m_Button, 0, 0);

	connect(m_Button, SIGNAL(clicked()), this, SLOT(bigClicked()));

    initLayout();

}
