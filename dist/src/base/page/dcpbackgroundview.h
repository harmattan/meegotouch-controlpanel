#ifndef DUIBACKGROUNDVIEW_H
#define DUIBACKGROUNDVIEW_H

#include <duiwidgetview.h>
#include <duistylable.h>

class DuiWidgetController;

class DcpBackgroundView : public DuiStylable<DcpBackgroundView, DuiWidgetView>
// class DcpBackgroundView : public DuiWidgetView
{
	public:
		DcpBackgroundView(DuiWidgetController *controller);

		virtual void paint(QPainter *painter, 
				   const QStyleOptionGraphicsItem *option, 
				   QWidget* widget);

		virtual void setGeometry(const QRectF &rect);
	        virtual QRectF boundingRect() const;

		static void registerStyleAttributes(DuiStyleDescription &description);

	protected:
		virtual QSizeF sizeHint(Qt::SizeHint which, 
				        const QSizeF & constraint = QSizeF()) const;

	private:
		DuiWidgetController *m_viewport;

		QPixmap *m_background;
};
#endif // DUIBACKGROUNDVIEW_H
