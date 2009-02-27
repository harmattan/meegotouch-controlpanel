#include "mainwindow.h"
#include "mainview.h"

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
	if (m_view) 
		delete m_view;
}


void MainWindow::initWindow() 
{
	m_view = new MainView();
	m_view->setGeometry(QRectF(0, 0,
				DuiDeviceProfile::instance()->width(),
				DuiDeviceProfile::instance()->height()));

	scene()->setBackgroundBrush(QColor(0, 0, 0, 255));
	scene()->addItem(m_view);
}
