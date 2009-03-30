#ifndef DCPBACKGROUNDLINEVIEW_H
#define DCPBACKGROUNDLINEVIEW_H

#include <duiwidgetview.h>
#include <duistylable.h>

class DcpBackgroundLineView: public DuiWidgetView
{
    Q_OBJECT
    DUI_STYLABLE

public:
    DcpBackgroundLineView(DuiWidgetController* controller);
    virtual ~DcpBackgroundLineView();

    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;

    void setLinePosition(qreal pos);
protected:
    virtual void drawBackground(QPainter* painter,
                                const QStyleOptionGraphicsItem* option) const;
    virtual void styleUpdated();
    virtual void resizeEvent ( QGraphicsSceneResizeEvent * event );

private:
    Q_DISABLE_COPY(DcpBackgroundLineView);

    void updateGraphics();

    qreal m_LinePosition;
    const QPixmap* m_Background;
    DuiWidgetController* m_Controller;
};


#endif // DCPBACKGROUNDLINEVIEW_H

