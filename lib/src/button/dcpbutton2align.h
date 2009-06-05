#ifndef DCPBUTTON2ALIGN_H
#define DCPBUTTON2ALIGN_H

#include "dcpbutton2.h"
class DuiLayout;
class DuiLinearLayoutPolicy;

class DcpButton2Align: public DcpButton2 {
    Q_OBJECT
public:
    DcpButton2Align(DuiWidget* parent, bool);

    void setWidgetAlignment(Qt::Alignment align);

protected:
    virtual DuiLayout* createLayout();
    void setAlignment(Qt::Alignment align);

    DuiWidget* alignedWidget();
    void setAlignedWidget(DuiWidget* widget);

private:
    void putupWidgets();
    DuiLayout* m_VertLayout;
    DuiLinearLayoutPolicy* m_VertLayoutPolicy;
    DuiWidget* m_AlignedWidget;
    Qt::Alignment m_Alignment;
};


#endif // DCPBUTTON2ALIGN_H
