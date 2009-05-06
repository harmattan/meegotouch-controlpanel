#include "dcplabel2component.h"

#include <duilabel.h>
#include <duibutton.h>
#include <duitheme.h>

#include "dcpappletmetadata.h"

#include <QDebug>

#include "dcpbutton.h"


DcpLabel2Component::DcpLabel2Component(
                            DcpCategory *category,
                            DcpAppletMetadata * metadata,
                            const QString& title,
                            QGraphicsWidget *parent):
    DcpBasicComponent(category, metadata, title, parent)
{
    createContents();
}


DcpLabel2Component::~DcpLabel2Component()
{
}


void DcpLabel2Component::createContents()
{

	m_Button = new DcpButton(DCPLABEL2, "", this);

	m_Button->setText(metadata()->text1(), metadata()->text2());
   	m_WidgetLayoutPolicy->addItemAtPosition(m_Button, 0, 0);

	connect(m_Button, SIGNAL(clicked()), this, SLOT(bigClicked()));

    initLayout();

}

// FIXME: move this to basiccomponent once it has the DcpButton 
void DcpLabel2Component::setBgObjectName(const QString& objectName) {
    m_Button->setObjectName(objectName);
}

