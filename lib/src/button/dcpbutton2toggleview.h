
#ifndef DCPBUTTON2TOGGLEIEW_H
#define DCPBUTTON2TOGGLEIEW_H

#include <DuiWidgetView>

#include <QGraphicsSceneMouseEvent>
#include "dcpbutton.h"

#include "dcpbutton2imageview.h"

#include "dcpbuttonmodel.h"
#include "dcpbuttonstyle.h"

class QPainter;

class DcpButton2ToggleView : public DcpButton2ImageView
{
    Q_OBJECT
//    DUI_STYLABLE
	
	DUI_VIEW(DcpButtonModel, DcpButtonStyle)

public:
    DcpButton2ToggleView(DcpButton *controller);

    virtual ~DcpButton2ToggleView();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = NULL);

	virtual void paintToggleLeft(QPainter *painter);
	virtual void paintToggleRight(QPainter *painter);

//	virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const ;

	virtual QRectF boundingRect() const;

protected:
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    Q_DISABLE_COPY(DcpButton2ToggleView);

    bool m_EnableToggle;

	const QPixmap *m_ToggleOn;
	const QPixmap *m_ToggleOff;

	enum {LEFTSIDE, RIGHTSIDE};

	int m_Side;
};

#endif
