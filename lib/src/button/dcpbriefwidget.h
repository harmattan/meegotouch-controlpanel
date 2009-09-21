#ifndef DCPBRIEFWIDGET_H
#define DCPBRIEFWIDGET_H

#include <DuiWidget>
class DcpAppletMetadata;
class DcpButton2;
class DcpButton2Image;
class DcpButton2Toggle;
class QShowEvent;
class QHideEvent;

class DcpBriefWidget: public DuiWidget {
    Q_OBJECT
public:
	DcpBriefWidget(DcpAppletMetadata* metadata, DuiWidget* parent = 0);
    void setMetadata(DcpAppletMetadata* metadata);
    DcpAppletMetadata* metadata() const {return m_Metadata;}

	~DcpBriefWidget();
public slots:
    void updateContents();

signals:
    void clicked();

protected:
    virtual void showEvent ( QShowEvent * event );
    virtual void hideEvent ( QHideEvent * event );
    DcpButton2Image* constructImage(const DcpAppletMetadata* metadata);
    DcpButton2Toggle* constructToggle(const DcpAppletMetadata* metadata);

    DcpButton2* m_RealWidget;
    DcpAppletMetadata* m_Metadata;
    bool m_Hidden;
};


#endif // DCPBRIEFWIDGET_H
