#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <duiwidget.h>

class DuiPannableViewport;

class MainView : public DuiWidget 
{
	Q_OBJECT

public:
	MainView(DuiWidget *parent = 0);
	virtual ~MainView();

protected:
	void initWidget();

private:
	DuiPannableViewport *m_viewport;
	DuiWidget *m_widget;
};
#endif // MAINVIEW_H
