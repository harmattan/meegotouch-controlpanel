#include <QtGui>
#include <QDebug>
#include <DuiAction>
#include <duitheme.h>

#include "languageapplet.h"
#include "languagewidget.h"
#include "dcpwidget.h"
#include "dcplanguage.h"
#include "languagetranslation.h"

#include "languagebrief.h"

#include "keyboarddialog.h"
#include "displaydialog.h"

Q_EXPORT_PLUGIN2(languageapplet, LanguageApplet)

const QString cssDir = "/usr/share/duicontrolpanel/themes/style/";

void LanguageApplet::init(QString part)
{
    DuiTheme::loadCSS(cssDir + "languageapplet.css");

    if (part == DcpLanguage::KeyDisplay) {
        m_PartIndex = DcpLanguage::Display;
    } else if (part == DcpLanguage::KeyKeyboard) {
        m_PartIndex = DcpLanguage::Keyboard;
    } else if (part == DcpLanguage::KeyMain) {
        m_PartIndex = DcpLanguage::Main;
    } else {
        m_PartIndex = DcpLanguage::None;
    }
}

DcpWidget* LanguageApplet::constructWidget(int widgetId)
{
    if (m_PartIndex != DcpLanguage::None && !widgetId) {
        widgetId = m_PartIndex;
    }
    switch (widgetId) {
        case DcpLanguage::Display: {
            DisplayDialog* dialog = new DisplayDialog();
            dialog->exec();
            break;
        }
        case DcpLanguage::Keyboard: {
            KeyboardDialog* dialog = new KeyboardDialog();
            dialog->exec();
            break;
        }
        case DcpLanguage::None:
        case DcpLanguage::Main:
            return mainPage();
        default:
            break;
    }
    return NULL;
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

