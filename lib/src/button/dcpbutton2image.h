#ifndef DCPBUTTON2IMAGE_H
#define DCPBUTTON2IMAGE_H

#include "dcpbutton2.h"
class DuiImage;

class DcpButton2Image: public DcpButton2 {
    Q_OBJECT
public:
    DcpButton2Image(DuiWidget* parent = 0);

    virtual DuiLayout* createLayout();

    void setPixmap (const QPixmap* pixmap);
    void setImageName (const QString& imageName);
    void setBorderPixmap (const QPixmap* pixmap);

private:
    DuiImage* m_Image;
};


#endif // DCPBUTTON2IMAGE_H
