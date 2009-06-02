#ifndef DCPBRIEFWIDGET_H
#define DCPBRIEFWIDGET_H

#include <DuiWidget>
class DcpAppletMetadata;
class DcpButton2;
class DuiLinearLayoutPolicy;

class DcpBriefWidget: public DuiWidget {
    Q_OBJECT
public:
	DcpBriefWidget(DcpAppletMetadata* metadata, DuiWidget* parent = 0);
    void setMetadata(DcpAppletMetadata* metadata);

protected:
    DuiLinearLayoutPolicy* m_Policy;
    DcpButton2* m_RealWidget;
};


#endif // DCPBRIEFWIDGET_H
