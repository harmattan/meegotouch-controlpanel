#ifndef SERVICESCONTAINER_H
#define SERVICESCONTAINER_H

#include <duiwidget.h>
class QPixmap;
class DuiLabel;
class DuiLayout;

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
    const QPixmap *m_Background;
    DuiLabel *m_Caption;
    DuiLayout *m_MainLayout;
}; 
#endif // SERVICESCONTAINER_H
