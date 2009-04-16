#ifndef DCPLABEL2_H
#define DCPLABEL2_H

#include "dcpbasiccomponent.h"

class DuiLabel;
class DuiButton;
class DuiLinearLayout;
class DuiGridLayout;
class DcpAppletMetadata;
class DcpButton;

class DcpLabel2Component: public DcpBasicComponent
{
    Q_OBJECT
public:
    DcpLabel2Component(DcpCategory *category,
                       DcpAppletMetadata* metadata,
                       const QString& title="",
                       QGraphicsWidget *parent=0);
    ~DcpLabel2Component();
    void setBgObjectName(const QString& objectName);

    virtual void createContents();

protected:
//		DuiLabel* m_DownLabel;
		DcpButton *m_Button;

};

#endif // DCPLABEL2_H
