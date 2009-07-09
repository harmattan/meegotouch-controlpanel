#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DuiApplicationWindow>
#include "pages.h"

class DcpPage;
class MainWindow : public DuiApplicationWindow
{
    Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow();
};

#endif // MAINWINDOW_H
