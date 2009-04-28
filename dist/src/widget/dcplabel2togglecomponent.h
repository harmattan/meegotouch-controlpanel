#ifndef DCPLABEL2TOGGLE_H
#define DCPLABEL2TOGGLE_H

#include "dcpbasiccomponent.h"

class DuiLabel;
class DuiButton;
class DuiLinearLayout;
class DuiGridLayout;
class DcpAppletMetadata;
class DcpButton;

class DcpLabel2ToggleComponent: public DcpBasicComponent
{
    Q_OBJECT
public:
    DcpLabel2ToggleComponent(DcpCategory *category,
                       DcpAppletMetadata* metadata,
                       const QString& title="",
                       QGraphicsWidget *parent=0);
    ~DcpLabel2ToggleComponent();
  
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

    bool m_EnableSmallToggle;

    Qt::Alignment m_Alignment;
};


#endif // DCPLABEL2BUTTON_H
