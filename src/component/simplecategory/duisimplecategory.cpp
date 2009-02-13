#include <duisimplecategory.h>
#include <duilinearlayout.h>
#include <duilabel.h>
DuiSimpleCategory::DuiSimpleCategory(const QString& title,
                                 QGraphicsWidget *parent) :
    DuiSettingsCategory(title, parent)
				
{
    createContents();
    resize(200, 200);
}

void 
DuiSimpleCategory::createContents()
{
	m_Layout = new DuiLinearLayout(Qt::Vertical);
//    DuiLabel *caption = new DuiLabel(title(), this);
    DuiLabel *caption2 = new DuiLabel("title", this);
    caption2->setAlignment(Qt::AlignCenter);
//	m_Layout->addItem(caption);
	m_Layout->addItem(caption2);
	setLayout(m_Layout);
}

void 
DuiSimpleCategory::add(DuiSettingsComponent *component)
{
	m_Layout->addItem(component);
	DuiSettingsCategory::add(component);
}
void 
DuiSimpleCategory::paint (QPainter *painter, 
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget)
{
    Q_UNUSED(option);                                                       
    Q_UNUSED(widget);                                                                            
                                                                                
    painter->drawRect(0, 0, size().width(), size().height());                   
	//DuiSettingsCategory::paint(painter, option, widget);
}

void 
DuiSimpleCategory::onOrientationChange (const Dui::Orientation &orientation)
{
    Q_UNUSED(orientation);	
}
