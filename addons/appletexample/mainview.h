#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <duiapplicationpage.h>

class DuiPannableViewport;

class MainView : public DuiApplicationPage
{
	Q_OBJECT

public:
    MainView();
	virtual ~MainView();
    void createContent();
    virtual void organizeContent(Dui::Orientation);

protected:
    void resizeEvent ( QGraphicsSceneResizeEvent * event );
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
            QWidget *widget);

private:
	DuiPannableViewport *m_viewport;
	DuiWidget *m_widget;
};
#endif // MAINVIEW_H
