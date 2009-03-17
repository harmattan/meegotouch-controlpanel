#ifndef SERVICESCONTAINER_H
#define SERVICESCONTAINER_H

#include <duiwidget.h>
class QPixmap;
class DuiLabel;
class DuiLinearLayout;

class ServicesContainer : public DuiWidget 
{
    Q_OBJECT

public:
    ServicesContainer(QGraphicsWidget *parent = 0);
    virtual ~ServicesContainer();

    //! \reimp
    virtual void paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *options,
                  QWidget *parent = 0);
    //! \reimp_end
    
    //! \reimp
    virtual void resizeEvent(QGraphicsSceneResizeEvent *event);
    //! \reimp_end
    
    void addServices(const QString &name);

protected:
    void initContainer();

private:
    const QPixmap   *m_background;
    DuiLabel        *m_caption;
    DuiLinearLayout *m_mainLayout;
}; 
#endif // SERVICESCONTAINER_H
