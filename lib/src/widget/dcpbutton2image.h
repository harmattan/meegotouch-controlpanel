#ifndef DCPBUTTON2IMAGE_H
#define DCPBUTTON2IMAGE_H

#include "dcpbutton2align.h"
class DuiImage;

class DcpButton2Image: public DcpButton2Align {
    Q_OBJECT
public:
    DcpButton2Image(DuiWidget* parent = 0);

    void setImageName (const QString& imageName);

protected:
    virtual QGraphicsLayout* createLayout();
    DuiImage* imageWidget();
    DuiImage* m_Image;
};


#endif // DCPBUTTON2IMAGE_H
