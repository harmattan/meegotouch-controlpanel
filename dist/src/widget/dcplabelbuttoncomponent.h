#ifndef DCPLABELBUTTON_H
#define DCPLABELBUTTON_H

#include "dcpbasiccomponent.h"

class DuiLabel;
class DuiButton;
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

    virtual void setEnableButton(bool enable);

    public slots:
        void smallClickedOn();
        void smallClickedOff();
        void disableClicked();


    protected:
        DuiButton* m_SmallButtonOn;
        DuiButton* m_SmallButtonOff;
        DuiButton* m_DisableButton;

};


#endif // DCPLABELBUTTON_H
