#ifndef SKELETONAPPLET_H
#define SKELETONAPPLET_H

#include <DcpAppletIf>
#include <QObject>
class DcpWidget;
class DuiAction;

class SkeletonApplet : public QObject, public DcpAppletIf 
{
	Q_OBJECT
	Q_INTERFACES(DcpAppletIf)

public:
    virtual void init();
	virtual DcpWidget* constructWidget(int widgetId);

	virtual DcpWidget* pageMain();
/*  Applet can have more 'pages'. Each page must be a DcpWidget subclass
	virtual DcpWidget* page1();
	virtual DcpWidget* page2();
*/
    virtual QString title() const;
    virtual QVector<DuiAction *> viewMenuItems();
    virtual DcpBrief* constructBrief(int);
};
#endif // SKELETONAPPLET_H
