#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DuiApplicationWindow>

class MainWindow : public DuiApplicationWindow 
{
	Q_OBJECT

public:
	MainWindow();
	virtual ~MainWindow();

protected:
	void initWindow();

private:
	DuiWidget *m_view;
};
#endif // MAINWINDOW_H
