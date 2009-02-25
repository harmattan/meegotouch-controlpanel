#include "mainview.h"
#include "exampleappletinterface.h"

#include <duilinearlayout.h>
#include <QPluginLoader>
#include <QDir>
#include <QDebug>


MainView::MainView(DuiWidget *parent)
	 :DuiWidget(parent)
{
	initWidget();
}


MainView::~MainView()
{
}

void MainView::initWidget()
{
	DuiLinearLayout *mainLayout = new DuiLinearLayout(Qt::Vertical, this);
	mainLayout->setMargin(50);
	mainLayout->setPadding(5);

	m_viewport = new DuiPannableViewport(Qt::Vertical);
	
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
				m_widget = applet->constructWidget();
				if (m_widget) {
					m_viewport->setWidget(m_widget);
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

	mainLayout->addItem(m_viewport);
}
