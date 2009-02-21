#include <duiapplication.h>
#include "mainwindow.h"

int main(int argc, char **argv) {
	DuiApplication duiApp(argc, argv);
	
	MainWindow window;
	window.show();

	return duiApp.exec();
}
