#ifndef HELLOWIDGET_H
#define HELLOWIDGET_H

#include <DuiWidget>
class DuiLabel;

class HelloWidget : public DuiWidget 
{
	Q_OBJECT
		
public:
	HelloWidget(QGraphicsWidget *parent = 0);
	virtual ~HelloWidget();

	void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem *option,
			   QWidget *widget);

protected:
	void initWidget();
		
private:
	DuiLabel *m_brightnessLabel;
	DuiLabel *m_screenLabel;
		
private slots:
	virtual void setBrightnessLabel(int value);
	virtual void setScreenLabel(int value);
};
#endif // HELLOWIDGET_H
