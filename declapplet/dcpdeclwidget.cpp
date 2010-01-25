#include "dcpdeclwidget.h"

#include <QGraphicsLinearLayout>
#include <QFile>
#include <DuiSettingsLanguageParser>
#include <DuiSettingsLanguageBinary>
#include <DuiSettingsLanguageWidget>
#include <DuiSettingsLanguageWidgetFactory>
#include <DuiGConfDataStore>
#include <DuiLabel>

#include <QtDebug>

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
    Q_ASSERT(binary);

    QString gpath = binary->keys().first();
    qDebug() << gpath;
    DuiGConfDataStore* datastore = new DuiGConfDataStore(gpath);

    DuiSettingsLanguageWidget* widget =
        DuiSettingsLanguageWidgetFactory::createWidget(*binary, datastore );
    Q_ASSERT(widget);
    layout->addItem(widget);
}

void DcpDeclWidget::createErrorLabel(const QString& text)
{
    DuiLabel* label = new DuiLabel(this);
    label->setText(text);
    ((QGraphicsLinearLayout*)(layout()))->addItem(label);
}

