#ifndef DCPAPPLETIF_H
#define DCPAPPLETIF_H

#include <QtPlugin>

class DcpWidget;

class DcpAppletIf {
public:
    virtual ~DcpAppletIf() {}
	virtual DcpWidget* constructWidget() = 0;
    virtual QString title() const = 0;
};

Q_DECLARE_INTERFACE(DcpAppletIf, "com.nokia.dui.core.DcpAppletIf/1.0")

#endif // DCPAPPLETIF_H

