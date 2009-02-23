#ifndef HELLOAPPLET_H
#define HELLOAPPLET_H

#include "exampleappletinterface.h"
#include <QObject>

class HelloApplet : public QObject, public ExampleAppletInterface {
	Q_OBJECT
	Q_INTERFACES(ExampleAppletInterface)

	public:
		virtual DuiWidget* constructWidget();
};

#endif // HELLOAPPLET_H
