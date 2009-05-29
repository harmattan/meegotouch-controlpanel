
#ifndef DCPBUTTONVIEW_H
#define DCPBUTTONVIEW_H

#include "dcpbuttonstyle.h"

#include <DuiWidgetView>

#include "dcpbutton.h"

#include "dcpbuttonmodel.h"



class QPainter;

class DcpButtonView : public DuiWidgetView
{
    Q_OBJECT
	DUI_VIEW(DcpButtonModel, DcpButtonStyle)
//    DUI_STYLABLE

public:
    DcpButtonView(DcpButton *controller);

    virtual ~DcpButtonView();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = NULL);
    virtual void paintBackground(QPainter *painter);
	void paintLine(QPainter *painter);
    virtual void paintTriangle(QPainter *painter);

	virtual void paintText(QPainter *painter);
	virtual void paintText2(QPainter *painter);		//2 line
	virtual void paintText1(QPainter *painter);		//1 line, empty second line

    void setText1(const QString& text);
    void setText2(const QString& text);

    int width();
    int height();

    void setAlignment(Qt::Alignment alignment);

	void setLine(bool line);

	void initMargins();

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

//    DcpButton &controller;
	Qt::Alignment m_Alignment;

	bool m_Bkgr;

	bool m_LineBool;

	int m_MarginLeft;
    int m_MarginRight;
    int m_MarginTop;
    int m_MarginBottom;
	int m_MarginMiddle;

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

/*
QRectF DcpButtonView::boundingRect() const
{
	return QRectF(0, 0, size().width(), size().height());
}
*/

#endif
