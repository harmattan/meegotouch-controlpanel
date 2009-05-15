#ifndef DCPAPPLETIF_H
#define DCPAPPLETIF_H

#include <QtPlugin>

class DcpWidget;
class DuiAction;
class DcpBrief;

class DcpAppletIf {
public:
    virtual ~DcpAppletIf() {}
    virtual void init() = 0;
	virtual DcpWidget* constructWidget(int widgetId) = 0;
    virtual QString title() const = 0;
    virtual QVector<DuiAction *> viewMenuItems() = 0;
    virtual DcpBrief* constructBrief() = 0;
};

Q_DECLARE_INTERFACE(DcpAppletIf, "com.nokia.dui.core.DcpAppletIf/1.0")

#endif // DCPAPPLETIF_H

