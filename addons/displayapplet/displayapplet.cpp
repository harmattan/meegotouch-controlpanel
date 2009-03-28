#include <QtGui>

#include "displayapplet.h"
#include "displaywidget.h"
#include "dcpwidget.h"

Q_EXPORT_PLUGIN2(displayapplet, DisplayApplet)
	
DcpWidget* DisplayApplet::constructWidget()
{
	return new DisplayWidget();
}

QString DisplayApplet::title() const
{
        return "Display";
}
