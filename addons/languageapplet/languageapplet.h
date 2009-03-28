#ifndef LANGUAGEAPPLET_H
#define LANGUAGEAPPLET_H

#include "dcpappletif.h"
#include <QObject>

class LanguageApplet : public QObject, public DcpAppletIf 
{
	Q_OBJECT
	Q_INTERFACES(DcpAppletIf)

public:
	virtual DuiWidget* constructWidget();

    virtual QString title() const;
};
#endif // HELLOLANGUAGE_H
