
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
	void paintLine(QPainter *painter);
    virtual void paintTriangle(QPainter *painter);
    virtual void paintText(QPainter *painter);

    void setText1(const QString& text);
    void setText2(const QString& text);

    Qt::Alignment stringToAlign(const QString& alignment);

    int width();
    int height();

    void setAlignment(Qt::Alignment alignment);

	void setLine(bool line);

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
		MarginTriangleAttribute,
		ImageNameAttribute,
		ImageSizeAttribute,

		MarginSpacerAttribute,

		BackgroundBorderAttribute,

		ToggleOnAttribute,
		ToggleOffAttribute

    };

	Qt::Alignment m_Alignment;

	bool m_Bkgr;

	bool m_LineBool;

};


inline void DcpButtonView::setAlignment(Qt::Alignment alignment)
{
	m_Alignment = alignment;
}

inline void DcpButtonView::setText1(const QString& text)
{
	m_Text1 = text;
}

inline void DcpButtonView::setText2(const QString& text)
{
	m_Text2 = text;
}

inline void DcpButtonView::setLine(bool line)
{
	m_LineBool = line;
}

#endif
