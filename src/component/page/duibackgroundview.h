#ifndef DUIBACKGROUNDVIEW_H
#define DUIBACKGROUNDVIEW_H

#include <duiwidgetview.h>
#include <duistylable.h>
#include <duipannableviewport.h>

class DuiBackgroundView : public DuiStylable<DuiBackgroundView, DuiWidgetView> 
{
	public:
		DuiBackgroundView();//DuiPannableViewport &widget);

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
		DuiPannableViewport& m_viewport;

		QPixmap m_background;
};
#endif // DUIBACKGROUNDVIEW_H
