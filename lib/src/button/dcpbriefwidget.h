#ifndef DCPBRIEFWIDGET_H
#define DCPBRIEFWIDGET_H

#include <DuiWidget>
class DcpAppletMetadata;
class DcpButton2;
class DcpButton2Image;
class DcpButton2Toggle;
class DuiLinearLayoutPolicy;

class DcpBriefWidget: public DuiWidget {
    Q_OBJECT
public:
	DcpBriefWidget(DcpAppletMetadata* metadata, DuiWidget* parent = 0);
    void setMetadata(DcpAppletMetadata* metadata);

public slots:
    void updateContents();

signals:
    void clicked();

protected:
    DcpButton2Image* constructImage(const DcpAppletMetadata* metadata);
    DcpButton2Toggle* constructToggle(const DcpAppletMetadata* metadata);

    DuiLinearLayoutPolicy* m_Policy;
    DcpButton2* m_RealWidget;
    DcpAppletMetadata* m_Metadata;
};


#endif // DCPBRIEFWIDGET_H