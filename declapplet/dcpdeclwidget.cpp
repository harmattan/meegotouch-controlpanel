#include "dcpdeclwidget.h"

#include <QGraphicsLinearLayout>
#include <QFile>
#include <DuiSettingsLanguageParser>
#include <DuiSettingsLanguageBinary>
#include <DuiSettingsLanguageWidget>
#include <DuiSettingsLanguageWidgetFactory>
#include <DuiGConfDataStore>
#include <DuiLabel>

#include <dcpdebug.h>

static const QString defaultPath = "/usr/lib/duicontrolpanel/uidescriptions/";

DcpDeclWidget::DcpDeclWidget(const QString& xmlPath)
{
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(
                                      Qt::Vertical, this);

    QString filePath = xmlPath.startsWith('/') ? xmlPath 
                                               : defaultPath + xmlPath;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        createErrorLabel(
            QString("Cannot find applet xml file %1").arg(filePath)
            );
        return;
    }

    DuiSettingsLanguageParser parser;
    if (!parser.readFrom(file)) {
        createErrorLabel(QString("Error parsing the ui description %1")
                         .arg(filePath));
        return;
    }

    DuiSettingsLanguageBinary* binary = parser.createSettingsBinary();
    if (!binary) {
        createErrorLabel(QString("Error parsing the ui description %1")
                         .arg(filePath));
        return;
    }

    QString gpath = binary->keys().first();
    DuiGConfDataStore* datastore = 0;
    if (gpath.startsWith("/")) {
        // TODO this is only working when all keys are in same dir
        gpath = gpath.left(gpath.lastIndexOf("/"));
        datastore = new DuiGConfDataStore(gpath);
    } else {
        DCP_WARNING("Fix gconf key paths in your xml: %s", qPrintable(filePath));
    }

    DuiSettingsLanguageWidget* widget =
        DuiSettingsLanguageWidgetFactory::createWidget(*binary, datastore );
    Q_ASSERT(widget);
    layout->addItem(widget);
}

void DcpDeclWidget::createErrorLabel(const QString& text)
{
    DuiLabel* label = new DuiLabel(this);
    label->setText("Error parsing the ui description, see log");
    DCP_WARNING(qPrintable(text));
    ((QGraphicsLinearLayout*)(layout()))->addItem(label);
}

