#ifndef DUMMYWIDGET_H
#define DUMMYWIDGET_H

#include <DcpWidget>
 
class DuiLabel;
class DuiButton;
class DummyWidget : public DcpWidget 
{
	Q_OBJECT
		
public:
	DummyWidget(const QString& text, QGraphicsWidget *parent = 0);
	virtual ~DummyWidget();

	void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem *option,
			   QWidget *widget);

protected:
	void initWidget();
private:
	DuiLabel    *m_Label;
};
#endif // DUMMYWIDGET_H
