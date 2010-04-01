#ifndef DUIAPPLICATIONWINDOW_H
#define DUIAPPLICATIONWINDOW_H

#include <QObject>
#include "duiwindow.h"

class DuiApplicationPage;

class DuiApplicationWindow: public QObject, public DuiWindow
{
    Q_OBJECT
public:
    DuiApplicationWindow();
    DuiApplicationPage* currentPage();

    static DuiApplicationWindow* activeWindow;

signals:
    void pageChanged(DuiApplicationPage *);

private:
};

#endif // DUIAPPLICATIONWINDOW_H

