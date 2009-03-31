#ifndef LANGUAGEAPPLET_H
#define LANGUAGEAPPLET_H

#include "dcpappletif.h"
#include <QObject>
class DcpWidget;
class LanguageApplet : public QObject, public DcpAppletIf 
{
	Q_OBJECT
	Q_INTERFACES(DcpAppletIf)

public:
    virtual void init(){};
	virtual DcpWidget* constructWidget(int widgetId=0);

    virtual QString title() const;
};
#endif // HELLOLANGUAGE_H
