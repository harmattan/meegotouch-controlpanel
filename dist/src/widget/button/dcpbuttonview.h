
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

		QString m_Text1;
		QString m_Text2;

    DcpButton &controller;

    Q_DISABLE_COPY(DcpButtonView);
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
