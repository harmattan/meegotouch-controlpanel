#ifndef DCPLABEL2IMAGE_H
#define DCPLABEL2IMAGE_H

#include "dcpbasiccomponent.h"
#include <QPixmap>

class DuiLabel;
class DuiButton;
class DuiImage;
class DuiLinearLayout;
class DuiGridLayout;
class DcpAppletMetadata;

class DcpLabel2ImageComponent: public DcpBasicComponent
{
    Q_OBJECT
public:
    DcpLabel2ImageComponent(DcpCategory *category,
                            DcpAppletMetadata* metadata,
                            Qt::Alignment alignment = Qt::AlignRight,
                            const QString& title="",
                            QGraphicsWidget *parent=0);
    ~DcpLabel2ImageComponent();

    virtual void createContents();

protected:
      void initRight();
      void initLeft();

    protected:
        DuiLabel* m_DownLabel;
        DuiImage *m_Image;

        QString m_UpLabelText;
        QString m_DownLabelText;


        int m_SmallWidth;
        int m_SpaceWidth;
        int m_ImageWidth;
    
        int m_TriangleSize;
    
        int m_Width;
        
        int m_Height;
    
        int m_ImageSize;

        Qt::Alignment m_Alignment;

};


#endif // DCPLABEL2IMAGE_H
