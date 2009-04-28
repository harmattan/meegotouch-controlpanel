#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include "dcpwidget.h"

class QPixmap;
class DuiLabel;
class DuiLayout;
class LanguageLabelButtonContainer;

class DisplayWidget : public DcpWidget
{
    Q_OBJECT

public:
    DisplayWidget(QGraphicsWidget *parent = 0);
    virtual ~DisplayWidget();
    //! reimp
    virtual void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);
    //! reimp_end

signals:
    void clicked();

protected:
    void initWidget();
    //! reimp
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    virtual void resizeEvent(QGraphicsSceneResizeEvent *event);
    //! reimp_end

private:
    const QPixmap *m_Background;
    DuiLabel *m_TitleLabel;
    DuiLayout *m_ContLayout;

private slots:
    virtual void removeContainer(LanguageLabelButtonContainer*);
};
#endif //DISPLAYWIDGET_H
