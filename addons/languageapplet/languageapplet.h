#ifndef LANGUAGEAPPLET_H
#define LANGUAGEAPPLET_H

#include "exampleappletinterface.h"
#include <QObject>

class LanguageApplet : public QObject, public ExampleAppletInterface 
{
	Q_OBJECT
	Q_INTERFACES(ExampleAppletInterface)

public:
	virtual DuiWidget* constructWidget();
};
#endif // HELLOLANGUAGE_H