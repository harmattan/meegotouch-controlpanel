/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

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
    void startPageForReal(const PageHandle &handle);

    // stores the startpage until the app is not started, after that it is 0
    PageHandle *m_StartPage; 
};


#endif
