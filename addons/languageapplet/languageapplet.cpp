#include <QtGui>
#include <QDebug>
#include <DuiAction>
// #include <duiapplication.h>

#include "languageapplet.h"
#include "languagewidget.h"
#include "dcpwidget.h"
#include "dcplanguage.h"
#include "languagetranslation.h"

#include "languagebrief.h"

Q_EXPORT_PLUGIN2(languageapplet, LanguageApplet)

void LanguageApplet::init(QString part)
{
    m_WidgetIndex = DcpLanguage::Main;
} 

DcpWidget* LanguageApplet::constructWidget(int widgetId)
{
	switch (widgetId)
    {
        case DcpLanguage::Main:
                return mainPage();
                break;
        default:
                qWarning() << "Page Unknown";
                return 0;
                break;
    }
}

DcpWidget* LanguageApplet::mainPage()
{
    return new LanguageWidget();
}

QString LanguageApplet::title() const
{
        return DcpLanguage::AppletTitle;
}

QVector<DuiAction*> LanguageApplet::viewMenuItems()
{
    QVector<DuiAction*> vector;
    
    // closeAction
    /* DuiAction *closeAction = new DuiAction(DcpLanguage::QuitSettingsMenuText, this);
    closeAction->setPossibleLocations(DuiAction::ViewMenu);
    connect(closeAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
    vector.push_back(closeAction);*/

    return vector;    
}

DcpBrief* LanguageApplet::constructBrief()
{
    return new LanguageBrief();
}

