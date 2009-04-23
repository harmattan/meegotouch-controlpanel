
#ifndef DCPBUTTON2IMAGEVIEW_H
#define DCPBUTTON2IMAGEVIEW_H

#include <DuiWidgetView>
#include "dcpbutton.h"

#include "dcpbutton2view.h"

class QPainter;

class DcpButton2ImageView : public DcpButton2View
{
    Q_OBJECT
    DUI_STYLABLE

public:
    DcpButton2ImageView(DcpButton &controller);

    virtual ~DcpButton2ImageView();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = NULL);

		virtual void paintTextLeft(QPainter *painter);
		virtual void paintImageLeft(QPainter *painter);

		virtual void paintTriangleRight(QPainter *painter);
		virtual void paintTextRight(QPainter *painter);
		virtual void paintImageRight(QPainter *painter);

private:
    Q_DISABLE_COPY(DcpButton2ImageView);
};

#endif
