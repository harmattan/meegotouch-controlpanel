#ifndef DCPAPPLETWIDGET_H
#define DCPAPPLETWIDGET_H

#include <QObject>
class DcpWidget;
class DcpStylableWidget;
class QGraphicsWidget;

/*!
 * This is a temporary container class which is used to hide the
 * differences between DcpWidget and DcpStylableWidget
 */
class DcpAppletWidget: public QObject
{
    Q_OBJECT
public:
    DcpAppletWidget(DcpWidget* widget, QObject * parent = 0);
    DcpAppletWidget(DcpStylableWidget* widget, QObject * parent = 0);

    ~DcpAppletWidget();

    void setReferer (int widgetId);
    bool back ();
    bool pagePans () const;
    int getWidgetId ();
    bool setWidgetId (int widgetId);
    QString title() const;
    bool isProgressIndicatorVisible () const;

    QGraphicsWidget* graphicsWidget () const;

public slots:
    void setProgressIndicatorVisible (bool visible);

signals:
    void changeWidget (int widgetId);
    bool activatePluginByName (const QString &appletName) const;
    void closePage();
    void inProgress (bool isInProgress);

private:
    DcpWidget* m_Widget;
    DcpStylableWidget* m_StylableWidget;
};


#endif // DCPAPPLETWIDGET_H

