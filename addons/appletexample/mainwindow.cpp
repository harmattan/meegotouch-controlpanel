#include "mainwindow.h"
#include "hellowidget.h"
#include "helloapplet.h"

#include <QPluginLoader>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow()
	   :DuiApplicationWindow()
{
	initWindow();
}


MainWindow::~MainWindow()
{
	if (m_view) {
		delete m_view;
	}
}


void MainWindow::initWindow() 
{
	QString appletPlace;
	appletPlace += QDir::currentPath();
	appletPlace += "/lib/libexampleapplet.so";
	
	// qWarning() << appletPlace;

	QPluginLoader loader(appletPlace);

	if (loader.load()) {
		qDebug() << "Example applet is loaded.";
		QObject *object = loader.instance();

		if (object) {
			ExampleAppletInterface *applet = qobject_cast<ExampleAppletInterface*>(object);
			if (applet) {
				m_view = applet->constructWidget();
				if (m_view) {
					scene()->addItem(m_view);
					m_view->setGeometry(QRectF(0, 0,
								   DuiDeviceProfile::instance()->width(),
								   DuiDeviceProfile::instance()->height()));

					scene()->setBackgroundBrush(QColor(0, 0, 0, 255));
				} else {
					qWarning() << "applet->constructWidget() failed.";
				}
				
			} else {
				qWarning() << "Can't convert object to ExampleAppletInterface.";
			}

			delete applet;
			applet = NULL;
		} else {
			qWarning() << "Can't get instance from plugin loader.";
		}
	} else {
		qWarning() << "Example applet can't loaded.";
	}
}
