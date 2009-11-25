#ifndef DCPBRIEFWIDGET_H
#define DCPBRIEFWIDGET_H

#include <DuiWidget>
class DcpAppletMetadata;
class DcpButton;
class DcpButtonImage;
class DcpButtonToggle;
class QShowEvent;
class QHideEvent;

class DcpBriefWidget: public DuiWidget
{
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
    virtual void retranslateUi();
    virtual void showEvent ( QShowEvent * event );
    virtual void hideEvent ( QHideEvent * event );
    DcpButtonImage* constructImage(const DcpAppletMetadata* metadata);
    DcpButtonToggle* constructToggle(const DcpAppletMetadata* metadata);

    DcpButton* m_RealWidget;
    DcpAppletMetadata* m_Metadata;
    bool m_Hidden;
};


#endif // DCPBRIEFWIDGET_H
