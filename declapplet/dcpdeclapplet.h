#ifndef DCPDECLAPPLET_H
#define DCPDECLAPPLET_H

#include <DcpAppletIf>
#include <QObject>
#include <QString>
#include <QList>
class DcpWidget;
class DuiAction;

class DcpDeclApplet: public QObject, public DcpAppletIf
{
    Q_OBJECT
    Q_INTERFACES(DcpAppletIf)

public:
    virtual void init();
    virtual DcpWidget* constructWidget(int widgetId);

    virtual QString title() const;
    virtual QVector<DuiAction *> viewMenuItems();
    virtual DcpBrief* constructBrief(int);
    virtual int partID(const QString& xmlpath);

private:
    QList<QString> m_XmlPaths;
};

#endif // DCPDECLAPPLET_H
