#ifndef DCPBUTTONALIGN_H
#define DCPBUTTONALIGN_H

#include "dcpbutton.h"
class QGraphicsLayout;
class QGraphicsLinearLayout;

class DcpButtonAlign: public DcpButton {
    Q_OBJECT
public:
    DcpButtonAlign(DuiWidget* parent, bool);

    void setWidgetAlignment(Qt::Alignment align);

protected:
    virtual QGraphicsLayout* createLayout();
    void setAlignment(Qt::Alignment align);

    DuiWidget* alignedWidget();
    void setAlignedWidget(DuiWidget* widget);

private:
    void putupWidgets();
    DuiWidget* m_AlignedWidget;
    QGraphicsLinearLayout* m_VertLayout;
    Qt::Alignment m_Alignment;
};


#endif // DCPBUTTONALIGN_H

