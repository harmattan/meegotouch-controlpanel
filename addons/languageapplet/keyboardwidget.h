#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include "dcpwidget.h"

class QPixmap;
class DuiLayout;
class LanguageLabelButtonContainer;

class KeyboardWidget : public DcpWidget
{
    Q_OBJECT

public:
    KeyboardWidget(QGraphicsWidget *parent = 0);
    virtual ~KeyboardWidget();

    //! reimp
    virtual void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);
    
    virtual bool back();
    //! reimp_end

protected:
    void initWidget();
    //! reimp
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    virtual void resizeEvent(QGraphicsSceneResizeEvent *event);
    //! reimp_end

private:
    const QPixmap *m_Background;
    DuiLayout *m_ContLayout;
    class KeyboardSelectContainer *m_SelectCont;
private slots:
    virtual void removeContainer(LanguageLabelButtonContainer*);
};
#endif //KEYBOARDWIDGET_H
