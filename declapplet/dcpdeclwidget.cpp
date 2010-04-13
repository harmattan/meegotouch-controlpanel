#include "dcpdeclwidget.h"

#include <QGraphicsLinearLayout>
#include <QFile>
#include <MSettingsLanguageParser>
#include <MSettingsLanguageBinary>
#include <MSettingsLanguageWidget>
#include <MSettingsLanguageWidgetFactory>
#include <MGConfDataStore>
#include <MLabel>

#include <dcpdebug.h>

static const QString defaultPath = "/usr/lib/mcontrolpanel/uidescriptions/";

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

    MSettingsLanguageParser parser;
    if (!parser.readFrom(file)) {
        createErrorLabel(QString("Error parsing the ui description %1")
                         .arg(filePath));
        return;
    }

    MSettingsLanguageBinary* binary = parser.createSettingsBinary();
    if (!binary) {
        createErrorLabel(QString("Error parsing the ui description %1")
                         .arg(filePath));
        return;
    }

    QString gpath = binary->keys().first();
    MGConfDataStore* datastore = 0;
    if (gpath.startsWith("/")) {
        // TODO this is only working when all keys are in same dir
        gpath = gpath.left(gpath.lastIndexOf("/"));
        datastore = new MGConfDataStore(gpath);
    } else {
        DCP_WARNING("Fix gconf key paths in your xml: %s", qPrintable(filePath));
    }

    MSettingsLanguageWidget* widget =
        MSettingsLanguageWidgetFactory::createWidget(*binary, datastore );
    Q_ASSERT(widget);
    layout->addItem(widget);
}

void DcpDeclWidget::createErrorLabel(const QString& text)
{
    MLabel* label = new MLabel(this);
    label->setText("Error parsing the ui description, see log");
    DCP_WARNING(qPrintable(text));
    ((QGraphicsLinearLayout*)(layout()))->addItem(label);
}

