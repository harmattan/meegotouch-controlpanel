#ifndef DCPLABELBUTTON_H
#define DCPLABELBUTTON_H

#include "dcpbasiccomponent.h"

class DuiLabel;
class DuiButton;
class DuiLinearLayout;
class DuiGridLayout;
class DcpAppletMetadata;

class DcpLabelButtonComponent: public DcpBasicComponent
{
    Q_OBJECT
public:
    DcpLabelButtonComponent(DcpCategory *category,
                       DcpAppletMetadata* metadata,
                       const QString& title="",
                       QGraphicsWidget *parent=0);
    ~DcpLabelButtonComponent();


    virtual void createContents();

    virtual void setEnable(bool enable);


    protected:
        DuiButton* m_SmallButtonOn;
        DuiButton* m_SmallButtonOff;
        DuiButton* m_DisableButton;

};


#endif // DCPLABELBUTTON_H
