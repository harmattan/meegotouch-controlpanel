#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <DuiWidget>
class DuiLabel;

class DisplayWidget : public DuiWidget 
{
	Q_OBJECT
		
public:
	DisplayWidget(QGraphicsWidget *parent = 0);
	virtual ~DisplayWidget();

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
#endif // DISPLAYWIDGET_H
