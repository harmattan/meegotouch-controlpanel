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

const QString appletDir = "/usr/lib/duicontrolpanel/applets/";
const int viewportMargin = 45;

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
     Q_UNUSED(option);
     Q_UNUSED(widget);
     painter->setBrush(Qt::black);
     painter->drawRect(option->rect);
}

void MainView::createContent()
{
    DuiLinearLayout *mainLayout = new DuiLinearLayout(Qt::Vertical);
    mainLayout->setMargin(viewportMargin);

	m_viewport = new DuiPannableViewport(Qt::Vertical);
	
	QString appletPlace;
	appletPlace += appletDir + "liblanguageapplet.so";
	
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
                    m_widget->setMaximumWidth(DuiDeviceProfile::instance()->width() 
                                    - viewportMargin * 2);
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

    m_viewport->setMinimumSize(m_widget->size() + QSize(5, 0));
    mainLayout->addItem(m_viewport);
    this->setLayout(mainLayout);
}

void MainView::resizeEvent ( QGraphicsSceneResizeEvent * event ) 
{
    if (m_viewport) m_viewport->setMinimumSize(this->size());
    DuiApplicationPage::resizeEvent(event);
}

void MainView::organizeContent(Dui::Orientation) 
{
}
