#ifndef DCPBUTTON2IMAGE_H
#define DCPBUTTON2IMAGE_H

#include "dcpbutton2align.h"
class DuiImage;

class DcpButton2Image: public DcpButton2Align {
    Q_OBJECT
public:
    DcpButton2Image(DuiWidget* parent = 0);

    void setPixmap (const QPixmap* pixmap);
    void setImageName (const QString& imageName);
    void setBorderPixmap (const QPixmap* pixmap);

protected:
    virtual DuiLayout* createLayout();
    DuiImage* imageWidget();
    DuiImage* m_BorderWidget;
};


#endif // DCPBUTTON2IMAGE_H
