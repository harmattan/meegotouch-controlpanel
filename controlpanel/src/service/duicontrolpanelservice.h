#ifndef DUICONTROLPANELSERVICE_H
#define DUICONTROLPANELSERVICE_H

#include <QObject>

class DuiControlPanelService: public QObject
{
    Q_OBJECT
public:
    DuiControlPanelService();

public Q_SLOTS:
    void appletPage(const QString& appletName);
    void categoryPage(const QString& category);
    void mainPage();

};


#endif // DUICONTROLPANELSERVICE_H
