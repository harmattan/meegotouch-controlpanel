#ifndef DCPLABEL2BUTTON_H
#define DCPLABEL2BUTTON_H

#include "dcpbasiccomponent.h"

class DuiLabel;
class DuiButton;
class DuiLinearLayout;
class DuiGridLayout;
class DcpAppletMetadata;

class DcpLabel2ButtonComponent: public DcpBasicComponent
{
    Q_OBJECT
public:
    DcpLabel2ButtonComponent(DcpCategory *category,
                       DcpAppletMetadata* metadata,
                       const QString& title="",
                       QGraphicsWidget *parent=0);
    ~DcpLabel2ButtonComponent();
  
    virtual void createContents();

    virtual void setEnableButton(bool enable);

public slots:
    void smallClickedOn();
    void smallClickedOff();
    void disableClicked();


    protected:
        DuiButton* m_SmallButtonOn;
        DuiButton* m_SmallButtonOff;
        DuiButton* m_DisableButton;

        DuiLabel* m_DownLabel;

};


#endif // DCPLABEL2BUTTON_H
