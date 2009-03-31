#include <QtGui>

#include "languageapplet.h"
#include "languagewidget.h"
#include "dcpwidget.h"
Q_EXPORT_PLUGIN2(languageapplet, LanguageApplet)
	
DcpWidget* LanguageApplet::constructWidget(int widgetId)
{
	return new LanguageWidget();
}

QString LanguageApplet::title() const
{
        return "Language";
}
