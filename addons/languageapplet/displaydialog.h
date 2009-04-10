#ifndef DISPLAYDIALOG_H
#define DISPLAYDIALOG_H

#include "duidialog.h"

class QPixmap;
class DuiLabel;

class DisplayDialog : public DuiDialog
{
    Q_OBJECT

public:
    DisplayDialog();
    ~DisplayDialog();

//    void paint(QPainter *painter,
//               const QStyleOptionGraphicsItem *option,
//               QWidget *widget = 0);
 //   void resizeEvent(QGraphicsSceneResizeEvent *event);

protected:
    void initWidget();

private:
    const QPixmap   *m_background;
    DuiLabel        *m_titleLabel;
};
#endif //DISPLAYWIDGET_H
