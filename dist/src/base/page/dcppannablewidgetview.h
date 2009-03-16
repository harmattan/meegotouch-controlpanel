#ifndef DCPPANNABLEWIDGETVIEW_H
#define DCPPANNABLEWIDGETVIEW_H

#include <duipannablewidgetview.h>
#include <duistylable.h>

class DuiPannableWidget;

/** Extends the DuiPannableWidgetView with background drawing. */
class DcpPannableWidgetView : public DuiStylable<DcpPannableWidgetView, DuiPannableWidgetView>
{
    Q_OBJECT
	public:
        DcpPannableWidgetView(DuiPannableWidget *controller);
        virtual ~DcpPannableWidgetView();

		virtual void paint(QPainter *painter, 
				   const QStyleOptionGraphicsItem *option, 
				   QWidget* widget);

        static void registerStyleAttributes(DuiStyleDescription &description);
        virtual void styleUpdated ();

    private:
        DuiPannableWidget *m_viewport;

        const QPixmap *m_background;
};

#endif // DCPPANNABLEWIDGETVIEW_H
