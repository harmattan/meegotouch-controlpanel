#include <QtGui>
#include <QDebug>

#include "languageapplet.h"
#include "languagewidget.h"
#include "displaywidget.h"
#include "keyboardwidget.h"
#include "dcpwidget.h"
#include "dcplanguage.h"

Q_EXPORT_PLUGIN2(languageapplet, LanguageApplet)

void LanguageApplet::init()
{
    m_widgetIndex = DcpLanguage::Main;
} 

DcpWidget* LanguageApplet::constructWidget(int widgetId)
{
	switch (widgetId)
    {
        case DcpLanguage::Main:
                return mainPage();
                break;
        case DcpLanguage::Display:
                return displayPage();
                break;
        case DcpLanguage::Keyboard:
                return keyboardPage();
                break;
        default:
                qWarning() << "Page Unknown";
                break;
    }
}

DcpWidget* LanguageApplet::mainPage()
{
    return new LanguageWidget();
}

DcpWidget* LanguageApplet::displayPage()
{
    return new DisplayWidget();
}

DcpWidget* LanguageApplet::keyboardPage()
{
    return new KeyboardWidget();
}

QString LanguageApplet::title() const
{
        return "Language";
}
