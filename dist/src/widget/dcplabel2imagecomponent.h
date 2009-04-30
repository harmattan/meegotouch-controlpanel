#ifndef DCPLABEL2IMAGE_H
#define DCPLABEL2IMAGE_H

#include "dcpbasiccomponent.h"
class DcpAppletMetadata;

class DcpLabel2ImageComponent: public DcpBasicComponent
{
    Q_OBJECT
public:
    DcpLabel2ImageComponent(DcpCategory *category,
                            DcpAppletMetadata* metadata,
                            const QString& title="",
                            QGraphicsWidget *parent=0);
    ~DcpLabel2ImageComponent();

    virtual void createContents();
};


#endif // DCPLABEL2IMAGE_H
