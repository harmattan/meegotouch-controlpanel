#ifndef DCPBACKGROUNDCOMPONENT_H
#define DCPBACKGROUNDCOMPONENT_H

#include "dcpcomponent.h"

class DuiLabel;
class DuiLinearLayout;
#include <QPixmap>

class DcpBackgroundComponent: public DcpComponent
{
    Q_OBJECT
public:
    DcpBackgroundComponent(DcpCategory *category,
                            const QString& title="",
                            QGraphicsWidget *parent=0);
    ~DcpBackgroundComponent();

    virtual void setTitle(const QString& title);
    void setTitleAlignment(Qt::Alignment align);

        // Composite Pattern Interface
    virtual void add(DcpComponent *){}
    virtual void remove(DcpComponent *){}

    virtual void paint (QPainter * painter,
                        const QStyleOptionGraphicsItem * option,
                        QWidget * widget = 0 );

    virtual void createContents();

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

protected:
    void addItem ( QGraphicsLayoutItem * item );

private:
    DuiLabel *m_Caption;
    QPixmap m_Background;
    DuiLinearLayout *m_Layout;
};


#endif // DCPBACKGROUNDCOMPONENT_H
