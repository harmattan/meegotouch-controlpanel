#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DuiApplicationWindow>

class MainWindow : public DuiApplicationWindow 
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();

protected:
	void initWindow();

private:
    DuiApplicationPage *m_view;
};
#endif // MAINWINDOW_H
