#ifndef DCPLABEL2IMAGE_H
#define DCPLABEL2IMAGE_H

#include "dcpbasiccomponent.h"
#include <QPixmap>

class DuiLabel;
class DuiButton;
class DuiImage;
class DcpAppletMetadata;
class DcpButton;

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

protected:
    void initRight();
    void initLeft();

protected:
    DuiLabel* m_DownLabel;
    DuiImage* m_Image;

    QString m_UpLabelText;
    QString m_DownLabelText;

    DuiButton* m_SpacerButton;

    int m_SmallWidth;
    int m_SpaceWidth;
    int m_ImageWidth;

   
    int m_ImageSize;

    Qt::Alignment m_Alignment;

		DcpButton *m_Button;

};


#endif // DCPLABEL2IMAGE_H
