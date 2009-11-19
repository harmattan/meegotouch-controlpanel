#include "dcpdeclwidget.h"

#include <QGraphicsLinearLayout>
#include <QFile>
#include <DuiDeclarativeSettingsParser>
#include <DuiDeclarativeSettingsBinary>
#include <DuiDeclarativeSettings>
#include <DuiDeclarativeSettingsFactory>
#include <DuiGConfDataStore>
#include <DuiLabel>

static const QString defaultPath = "/usr/lib/duicontrolpanel/uidescriptions/";

DcpDeclWidget::DcpDeclWidget(const QString& xmlPath)
{
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(
                                      Qt::Vertical, this);

    // TODO memleaks in errors
    QString filePath = xmlPath.startsWith('/') ? xmlPath : defaultPath + xmlPath;
	QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        createErrorLabel(QString("Cannot find applet xml file %1").arg(filePath));
        return;
    }

    DuiDeclarativeSettingsParser parser;
    if (!parser.readFrom(file)) {
        createErrorLabel(QString("Error parsing the ui description %1")
                         .arg(filePath));
        return;
    }

    DuiDeclarativeSettingsBinary* binary = parser.createSettingsBinary();
    Q_ASSERT(binary);
    DuiGConfDataStore* datastore = new DuiGConfDataStore();
    foreach (QString key, binary->keys()) {
        datastore->addGConfKey(key, key);
    }
    DuiDeclarativeSettings* widget =
        DuiDeclarativeSettingsFactory::createWidget(*binary, datastore );
    Q_ASSERT(widget);
    layout->addItem(widget);
}

void DcpDeclWidget::createErrorLabel(const QString& text)
{
    DuiLabel* label = new DuiLabel(this);
    label->setText(text);
    ((QGraphicsLinearLayout*)(layout()))->addItem(label);
}

