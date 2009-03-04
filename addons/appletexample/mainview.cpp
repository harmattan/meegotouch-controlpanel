#include "mainview.h"
#include "exampleappletinterface.h"

#include <duipannableviewport.h>
#include <duilinearlayout.h>
#include <QPluginLoader>
#include <QDir>
#include <QtDebug>
#include <QGraphicsSceneResizeEvent>
#include <QStyleOptionGraphicsItem>
#include <duilabel.h>

MainView::MainView()
     :DuiApplicationPage(), m_viewport(NULL)
{
}


MainView::~MainView()
{
}

 void MainView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
            QWidget *widget)
 {
     painter->setBrush(Qt::black);
     painter->drawRect(option->rect);
 }


void MainView::createContent()
{
    DuiLinearLayout *mainLayout = new DuiLinearLayout(Qt::Vertical);
    mainLayout->setMargin(50);
    mainLayout->setPadding(5);

	m_viewport = new DuiPannableViewport(Qt::Vertical);
    m_viewport->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	
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

    m_viewport->setMinimumSize(this->size());
    mainLayout->addItem(m_viewport);
    this->setLayout(mainLayout);
}


void MainView::resizeEvent ( QGraphicsSceneResizeEvent * event ) {
    if (m_viewport) m_viewport->setMinimumSize(this->size());
    DuiApplicationPage::resizeEvent(event);
}


void MainView::organizeContent(Dui::Orientation) {
}
