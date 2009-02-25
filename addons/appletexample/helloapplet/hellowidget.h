#ifndef HELLOWIDGET_H
#define HELLOWIDGET_H

#include <DuiWidget>

class HelloWidget : public DuiWidget {
	public:
		HelloWidget(QGraphicsWidget *parent = 0);

		virtual ~HelloWidget();

		void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem *option,
			   QWidget *widget);

		
	protected:
		void initWidget();
};

#endif // HELLOWIDGET_H
