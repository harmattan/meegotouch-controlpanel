#ifndef DCPLABELCOMPONENT_H
#define DCPLABELCOMPONENT_H

#include "dcpbasiccomponent.h"
#include <QPixmap>

class DuiLabel;
class DuiButton;
class DuiLinearLayout;
class DuiGridLayout;
class DcpAppletMetadata;

class DcpLabelComponent: public DcpBasicComponent
{
    Q_OBJECT
public:
    DcpLabelComponent(DcpCategory *category,
                       DcpAppletMetadata* metadata,
                       const QString& title="",
                       QGraphicsWidget *parent=0);
    ~DcpLabelComponent();

    virtual void createContents();

};

#endif // DCPLABELCOMPONENT_H
