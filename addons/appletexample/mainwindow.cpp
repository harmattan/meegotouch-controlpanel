#include "mainwindow.h"
#include "mainview.h"

#include <duinavigationbar.h>
#include <QPluginLoader>
#include <QDebug>
#include <QDir>
#include <QGraphicsSceneResizeEvent>

MainWindow::MainWindow(QWidget *parent)
	   :DuiApplicationWindow(parent)
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
    m_view->appearNow();
    navigationBar()->setViewMenuButtonText("Language");
}
