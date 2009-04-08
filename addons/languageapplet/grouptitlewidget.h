#ifndef GROUPTITLEWIDGET_H
#define GROUPTITLEWIDGET_H

#include <DuiLabel>

class QPixmap;

class GroupTitleWidget : public DuiWidget
{
public:
    GroupTitleWidget(const QString &text, DuiWidget *parent = 0);
    ~GroupTitleWidget();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);
    void resizeEvent(QGraphicsSceneResizeEvent *event);

private:
    const QPixmap *m_background;
};
#endif // GROUPTITLEWIDGET_H
