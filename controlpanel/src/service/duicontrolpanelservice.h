#ifndef DUICONTROLPANELSERVICE_H
#define DUICONTROLPANELSERVICE_H

#include <QObject>
#include "pages.h"

class DuiControlPanelService: public QObject
{
    Q_OBJECT
public:
    DuiControlPanelService();
    void createStartPage();

public Q_SLOTS:
    bool appletPage(const QString& appletName);
    void categoryPage(const QString& category);
    void mainPage();

private:
    void sheduleStart (const PageHandle &handle);
    PageHandle *m_StartPage; // stores the startpage until 
                             // the app is not started,
                             // after that it is 0
};


#endif // DUICONTROLPANELSERVICE_H
