#include <DuiApplication>
#include <DuiApplicationWindow>
#include <DuiApplicationPage>
#include <DuiLabel>
#include <QGraphicsLinearLayout>

#include <QFile>
#include <DuiDeclarativeSettingsParser>
#include <DuiDeclarativeSettingsBinary>
#include <DuiDeclarativeSettings>
#include <DuiDeclarativeSettingsFactory>

int main(int argc, char** argv)
{
    Q_ASSERT(argc > 1);
    
    DuiApplication app(argc, argv);
    DuiApplicationWindow win;
    DuiApplicationPage page;
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(
            Qt::Vertical, page.centralWidget());
    layout->addItem(new DuiLabel("TEST"));


    /* -- */
    QFile file(argv[1]);
    Q_ASSERT(file.open(QIODevice::ReadOnly));
    
    DuiDeclarativeSettingsParser parser;
    if (!parser.readFrom(file)) {
        qDebug("Parser error");
        return 1;
    }
    DuiDeclarativeSettingsBinary* binary = parser.createSettingsBinary();
    Q_ASSERT(binary);
    
    DuiDeclarativeSettings* widget = DuiDeclarativeSettingsFactory::createWidget(*binary /*, datastore */);
    Q_ASSERT(widget);
    layout->addItem(widget);
    /* -- */

    page.appearNow();
    win.show();
    return app.exec();
}

