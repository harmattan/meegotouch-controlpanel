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
public slots:
    void changePage(Pages::Handle handle);
    void backClicked();
};

#endif // MAINWINDOW_H
