#ifndef DISPLAYAPPLET_H
#define DISPLAYAPPLET_H

#include "exampleappletinterface.h"
#include <QObject>

class DisplayApplet : public QObject, public ExampleAppletInterface 
{
	Q_OBJECT
	Q_INTERFACES(ExampleAppletInterface)

public:
	virtual DuiWidget* constructWidget();

    virtual QString title() const;
};
#endif // DISPLAYAPPLET_H
