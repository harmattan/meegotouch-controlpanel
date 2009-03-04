#include "mainwindow.h"
#include "mainview.h"

#include <QPluginLoader>
#include <QDebug>
#include <QDir>
#include <QGraphicsSceneResizeEvent>

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

    addPage(m_view);
    showPage(m_view);
}

