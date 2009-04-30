#include "dcplabel2togglecomponent.h"
#include "dcpappletmetadata.h"
#include "dcpbutton.h"

DcpLabel2ToggleComponent::DcpLabel2ToggleComponent( DcpCategory *category,
                                                    DcpAppletMetadata * metadata,
                                                    const QString& title,
                                                    QGraphicsWidget *parent):
                          DcpBasicComponent(category, metadata, title, parent)
{
	m_Alignment = metadata->align();
    createContents();
}


DcpLabel2ToggleComponent::~DcpLabel2ToggleComponent()
{
}


void DcpLabel2ToggleComponent::createContents()
{

	if ( m_Alignment==Qt::AlignLeft ) {
        m_Button = new DcpButton(DCPLABEL2TOGGLE);
		m_Button->setAlignment(Qt::AlignLeft);
	} else {
        m_Button = new DcpButton(DCPLABEL2TOGGLE);
		m_Button->setAlignment(Qt::AlignRight);
	}

	m_Button->setText(metadata()->text1(), metadata()->text2());
   	m_WidgetLayoutPolicy->addItemAtPosition(m_Button, 0, 0);

	connect(m_Button, SIGNAL(clicked()), this, SLOT(bigClicked()));

    initLayout();
}
