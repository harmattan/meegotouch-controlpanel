#ifndef DCPBACKGROUNDCOMPONENT_H
#define DCPBACKGROUNDCOMPONENT_H

#include "dcpcomponent.h"

class DuiLabel;
#include <QPixmap>

class DcpBackgroundComponent: public DcpComponent
{
    Q_OBJECT
public:
    DcpBackgroundComponent(DcpCategory *category,
                            const QString& title="",
                            QGraphicsWidget *parent=0);

    virtual void setTitle(const QString& title);
    void setTitleAlignment(Qt::Alignment align);

        // Composite Pattern Interface
    virtual void add(DcpComponent *){}
    virtual void remove(DcpComponent *){}
    virtual void createContents();

protected:
    void addItem ( QGraphicsLayoutItem * item );

    virtual void resizeEvent ( QGraphicsSceneResizeEvent * event );

private:
    const QPixmap *m_Background;
    class DuiLinearLayoutPolicy *m_Layout;
    DuiLabel *m_Caption;
};


#endif // DCPBACKGROUNDCOMPONENT_H
