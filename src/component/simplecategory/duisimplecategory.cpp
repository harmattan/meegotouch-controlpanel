#include <duisimplecategory.h>
#include <duilinearlayout.h>
#include <duilabel.h>
DuiSimpleCategory::DuiSimpleCategory(const QString& title,
                                 QGraphicsWidget *parent) :
    DuiSettingsCategory(title, parent)
				
{
    createContents();
}

void 
DuiSimpleCategory::createContents()
{
	m_Layout = new DuiLinearLayout(Qt::Vertical);
    DuiLabel *caption = new DuiLabel(title());
    DuiLabel *caption2 = new DuiLabel(title()+"_1");
    DuiLabel *caption3 = new DuiLabel(title()+"_2");
    caption2->setAlignment(Qt::AlignCenter);
    caption3->setAlignment(Qt::AlignRight);
    m_Layout->addItem(caption);
	m_Layout->addItem(caption2);
    m_Layout->addItem(caption3);
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
                                                                                
    painter->drawRect(boundingRect());
    DuiSettingsCategory::paint(painter, option, widget);
}

void 
DuiSimpleCategory::onOrientationChange (const Dui::Orientation &orientation)
{
    Q_UNUSED(orientation);	
}
