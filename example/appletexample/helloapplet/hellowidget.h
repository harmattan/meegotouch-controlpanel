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

		QSizeF minimumSize() const;

		QSizeF preferredSize() const;

		QSizeF maximumSize() const;

		
	protected:
		void initWidget();


	private:
		QSizeF m_minimumSize;

		QSizeF m_preferredSize;

		QSizeF m_maximumSize;
};

#endif // HELLOWIDGET_H
