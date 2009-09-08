#ifndef DATETIMEAPPLET_H
#define DATETIMEAPPLET_H

#include <DcpAppletIf>
#include <QObject>
#include <QMap>
class DcpWidget;
class DuiAction;

class DateTimeApplet : public QObject, public DcpAppletIf 
{
	Q_OBJECT
	Q_INTERFACES(DcpAppletIf)

public:
    virtual void init(QString part="");
	virtual DcpWidget* constructWidget(int widgetId);
    virtual DcpWidget* pageMain();
    virtual DcpWidget* pageTimeZone();
    virtual DcpWidget* pageDate();
    virtual DcpWidget* pageTime();
    virtual QString title() const;
    virtual QVector<DuiAction *> viewMenuItems();
    virtual DcpBrief* constructBrief();

private:
    int m_WidgetIndex;
    int m_PartIndex;
    QString m_Title;
    QMap<QString, int> m_Parts;
};
#endif // DATETIMEAPPLET_H

