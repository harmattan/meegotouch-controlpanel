#ifndef DISPLAYAPPLET_H
#define DISPLAYAPPLET_H

#include "dcpappletif.h"
#include <QObject>

class DisplayApplet : public QObject, public DcpAppletIf 
{
	Q_OBJECT
	Q_INTERFACES(DcpAppletIf)

public:
	virtual DuiWidget* constructWidget();

    virtual QString title() const;
};
#endif // DISPLAYAPPLET_H
