#ifndef DCPLABEL2_H
#define DCPLABEL2_H

#include "dcpbasiccomponent.h"

class DuiLabel;
class DuiButton;
class DuiLinearLayout;
class DuiGridLayout;
class DcpAppletMetadata;

class DcpLabel2Component: public DcpBasicComponent
{
    Q_OBJECT
public:
    DcpLabel2Component(DcpCategory *category,
                       DcpAppletMetadata* metadata,
                       const QString& title="",
                       QGraphicsWidget *parent=0);
    ~DcpLabel2Component();

    virtual void createContents();

    protected:

        DuiLabel* m_DownLabel;

};


#endif // DCPLABEL2_H