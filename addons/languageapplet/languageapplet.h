#ifndef LANGUAGEAPPLET_H
#define LANGUAGEAPPLET_H

#include "dcpappletif.h"
#include <QObject>
class DcpWidget;
class DuiAction;

class LanguageApplet : public QObject, public DcpAppletIf 
{
	Q_OBJECT
	Q_INTERFACES(DcpAppletIf)

public:
    virtual void init();
	virtual DcpWidget* constructWidget(int widgetId);

    virtual DcpWidget* mainPage();
    virtual DcpWidget* displayPage();
    virtual DcpWidget* keyboardPage();

    virtual QString title() const;
    virtual QVector<DuiAction*> viewMenuItems();

private:
    int m_widgetIndex;
};
#endif // HELLOLANGUAGE_H
