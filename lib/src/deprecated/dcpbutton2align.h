#ifndef DCPBUTTON2ALIGN_H
#define DCPBUTTON2ALIGN_H

#include "dcpbutton2.h"
#warning "DcpButton2Align is DEPRECATED, and will be removed soon! Use DcpButtonAlign instead."
class QGraphicsLayout;
class QGraphicsLinearLayout;

class DcpButton2Align: public DcpButton2 {
    Q_OBJECT
public:
    DcpButton2Align(DuiWidget* parent, bool);

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


#endif // DCPBUTTON2ALIGN_H

