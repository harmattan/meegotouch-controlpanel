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
    virtual void init(QString part="");
	virtual DcpWidget* constructWidget(int widgetId);
    virtual QString title() const;
    virtual QVector<DuiAction*> viewMenuItems();
    virtual DcpBrief* constructBrief();

private:
    DcpWidget* mainPage(int widgetId);

    int m_PartIndex;
};
#endif // HELLOLANGUAGE_H
