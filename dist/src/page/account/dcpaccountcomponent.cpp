#include "dcpaccountcomponent.h" 
#include "duiimagelabel.h" 
#include "duilinearlayout.h" 
#include "duitheme.h"
#include "dcpbutton.h"
#include <QGraphicsSceneMouseEvent>
#include <QtDebug>

const int BIG_WIDTH    = 350;
const int BIG_HEIGHT   =  90;
const int SMALL_WIDTH  =  80;
const int SMALL_HEIGHT =  80;
const int SMALL_X      =  10;
const int SMALL_Y      =   5;

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
    /* DuiLinearLayout *layout = new DuiLinearLayout(Qt::Vertical, this); 
    m_Label = new DuiImageLabel();
    m_Label->setText(title());
    m_Label->setImage(new DuiImage(DuiTheme::pixmap("W-Icon-flickr")));
    m_Label->setImageVisible(true);
    layout->addItem(m_Label);
    setLayout(layout); */
    DcpButton *button = new DcpButton(title(),
		    		      BIG_WIDTH,
				      BIG_HEIGHT,
				      "small",
				      SMALL_X,
				      SMALL_Y,
				      SMALL_WIDTH,
				      SMALL_HEIGHT,
				      true);
    
    setLayout(button->layout());
    connect(button, SIGNAL(clicked(QString)), this, SLOT(handleClick(QString)));
}


void DcpAccountComponent::mousePressEvent (QGraphicsSceneMouseEvent *event) 
{                                                                               
    switchToSubPage();                                                          
    event->accept();                                                            
}


void DcpAccountComponent::handleClick(QString name)
{
	if (name == "bigClicked") {
		switchToSubPage();
	}
}
