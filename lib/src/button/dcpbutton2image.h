#ifndef DCPBUTTON2IMAGE_H
#define DCPBUTTON2IMAGE_H

#include "dcpbutton2align.h"
class DuiButton;

class DcpButton2Image: public DcpButton2Align {
    Q_OBJECT
public:
    DcpButton2Image(DuiWidget* parent = 0);

    void setImageName (const QString& imageName);

protected:
    virtual DuiLayout* createLayout();
    DuiButton* imageWidget();
};


#endif // DCPBUTTON2IMAGE_H
