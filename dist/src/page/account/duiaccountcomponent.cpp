#include "duiaccountcomponent.h" 
#include "duiimagelabel.h" 
#include "duilinearlayout.h" 
#include "duitheme.h"
#include <QGraphicsSceneMouseEvent>
#include <QtDebug>
DuiAccountComponent::DuiAccountComponent(DuiSettingsCategory *category,
                                  const QString& title, 
				  QGraphicsWidget *parent) :
		 DuiSimpleComponent(category, title, parent)
{
    createContents();
}	 

void
DuiAccountComponent::createContents()
{
    DuiLinearLayout *layout = new DuiLinearLayout(Qt::Vertical); 
    m_Label = new DuiImageLabel();
    m_Label->setText(title());
    m_Label->setImage(new DuiImage(DuiTheme::pixmap("W-Icon-flickr")));
    m_Label->setImageVisible(true);
    layout->addItem(m_Label);
    setLayout(layout);
}
void DuiAccountComponent::mousePressEvent (QGraphicsSceneMouseEvent *event) 
{                                                                               
    switchToSubPage();                                                          
    event->accept();                                                            
}          
