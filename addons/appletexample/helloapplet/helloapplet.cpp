#include <QtGui>

#include "helloapplet.h"
#include "hellowidget.h"

Q_EXPORT_PLUGIN2(helloapplet, HelloApplet)
	
DuiWidget* HelloApplet::constructWidget()
{
	return new HelloWidget();
}
