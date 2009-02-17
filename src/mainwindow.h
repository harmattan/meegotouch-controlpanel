#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DuiApplicationWindow>
#include "pages.h"
class PageFactory;
class MainWindow : public DuiApplicationWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
public slots:
    void changePage(Pages::Id pageId);
    void homeClicked();
};

#endif // MAINWINDOW_H
