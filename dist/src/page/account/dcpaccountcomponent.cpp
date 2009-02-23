#include "dcpaccountcomponent.h" 
#include "duiimagelabel.h" 
#include "duilinearlayout.h" 
#include "duitheme.h"
#include <QGraphicsSceneMouseEvent>
#include <QtDebug>
DcpAccountComponent::DcpAccountComponent(DcpCategory *category,
                                  const QString& title, 
				  QGraphicsWidget *parent) :
		 DcpSimpleComponent(category, title, parent)
{
    createContents();
}	 

void
DcpAccountComponent::createContents()
{
    DuiLinearLayout *layout = new DuiLinearLayout(Qt::Vertical); 
    m_Label = new DuiImageLabel();
    m_Label->setText(title());
    m_Label->setImage(new DuiImage(DuiTheme::pixmap("W-Icon-flickr")));
    m_Label->setImageVisible(true);
    layout->addItem(m_Label);
    setLayout(layout);
}
void DcpAccountComponent::mousePressEvent (QGraphicsSceneMouseEvent *event) 
{                                                                               
    switchToSubPage();                                                          
    event->accept();                                                            
}          
