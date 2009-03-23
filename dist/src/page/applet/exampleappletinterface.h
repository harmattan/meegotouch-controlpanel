#ifndef EXMAPLEAPPLETINTERFACE_H
#define EXAMPLEAPPLETINTERFACE_H

#include <QtPlugin>

class DuiWidget;

class ExampleAppletInterface {
	public:
		virtual ~ExampleAppletInterface() {}

		virtual DuiWidget* constructWidget() = 0;

        virtual QString title() const = 0;
};

Q_DECLARE_INTERFACE(ExampleAppletInterface, "com.nokia.dui.core.ExampleAppletInterface/1.0")

#endif // EXAMPLEAPPLETINTERFACE_H
