#ifndef DCPBUTTONIMAGE_H
#define DCPBUTTONIMAGE_H

#include "dcpbuttonalign.h"
class DuiImage;

class DcpButtonImage: public DcpButtonAlign {
    Q_OBJECT
public:
    DcpButtonImage(DuiWidget* parent = 0);

    void setImageName (const QString& imageName);

protected:
    virtual QGraphicsLayout* createLayout();
    DuiImage* imageWidget();
    DuiImage* m_Image;
};


#endif // DCPBUTTONIMAGE_H
