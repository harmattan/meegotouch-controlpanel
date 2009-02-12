#include "duisimplecategory.h"
#include "duilinearlayout.h"
#include "duilabel.h"
DuiSimpleCategory::DuiSimpleCategory(const QString& title,
                                 QGraphicsWidget *parent) :
    DuiSettingsCategory(title, parent)
				
{
    createContents();
}

void 
DuiSimpleCategory::createContents()
{
	DuiLinearLayout *layout = new DuiLinearLayout(Qt::Vertical);
	DuiLabel *caption = new DuiLabel(title());

	layout->addItem(caption);
	setLayout(layout);
}

void 
DuiSimpleCategory::paint (QPainter *painter, 
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget)
{
	DuiSettingsCategory::paint(painter, option, widget);
}

void 
DuiSimpleCategory::onOrientationChange (const Dui::Orientation &orientation)
{
    Q_UNUSED(orientation);	
}
