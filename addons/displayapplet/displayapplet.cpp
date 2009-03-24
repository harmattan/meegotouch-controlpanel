#include <QtGui>

#include "displayapplet.h"
#include "displaywidget.h"

Q_EXPORT_PLUGIN2(displayapplet, DisplayApplet)
	
DuiWidget* DisplayApplet::constructWidget()
{
	return new DisplayWidget();
}

QString DisplayApplet::title() const
{
        return "Display";
}
