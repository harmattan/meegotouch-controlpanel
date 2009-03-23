#include <QtGui>

#include "languageapplet.h"
#include "languagewidget.h"

Q_EXPORT_PLUGIN2(languageapplet, LanguageApplet)
	
DuiWidget* LanguageApplet::constructWidget()
{
	return new LanguageWidget();
}

QString LanguageApplet::title() const
{
        return "Language";
}
