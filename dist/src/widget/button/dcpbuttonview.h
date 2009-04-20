
#ifndef DCPBUTTONVIEW_H
#define DCPBUTTONVIEW_H

#include <DuiWidgetView>
#include "dcpbutton.h"

class QPainter;

class DcpButtonView : public DuiWidgetView
{
    Q_OBJECT
    DUI_STYLABLE

public:
    DcpButtonView(DcpButton &controller);

    virtual ~DcpButtonView();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = NULL);
    virtual QRectF boundingRect() const;

		virtual void paintBackground(QPainter *painter);
		virtual void paintTriangle(QPainter *painter);
		virtual void paintText(QPainter *painter);


		void setText1(const QString& text);
		void setText2(const QString& text);

		int stringToAlign(const QString& align);

		int width();
		int height();

signals:
    void clicked();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    Q_DISABLE_COPY(DcpButtonView);

protected:

		QString m_Text1;
		QString m_Text2;

    DcpButton &controller;

	enum styleAttributes {
	
			MarginLeftAttribute,
			MarginRightAttribute,
			MarginTopAttribute,
			MarginBottomAttribute,
			MarginMiddleAttribute,
	
			BackgroundAttribute,
			BackgroundSizeAttribute,
	
			Font1Attribute,
			Font2Attribute,
	
			TextColor1Attribute,
			TextColor2Attribute,
	
			TextSize1Attribute,
			TextSize2Attribute,
	
			TextPos1Attribute,
			TextPos2Attribute,
	
			TextAlign1Attribute,
			TextAlign2Attribute,
	
			TriangleBackgroundAttribute,
			TriangleBackgroundSizeAttribute,
			TrianglePosAttribute,

			ImageNameAttribute,
			ImageSizeAttribute,
			ImageSpacerAttribute,

			BackgroundBorderAttribute
	
	};
};


inline void DcpButtonView::setText1(const QString& text)
{
		m_Text1 = text;
}

inline void DcpButtonView::setText2(const QString& text)
{
		m_Text2 = text;
}

#endif
