#include "dcpspec.h"

#include <QPixmap>

#include <QtDebug>

#include <duigridlayout.h>

#include <duitheme.h>

DcpSpec::DcpSpec(const QString& image, int width, int height, int smallWidth, int smallHeight, const QString& css)
{
        Q_UNUSED(css);
    m_Layout = new DuiGridLayout();

    m_Layout->setColumnMinimumWidth ( 0, smallWidth );
    m_Layout->setColumnMaximumWidth ( 0, smallWidth );

    m_Layout->setColumnMinimumWidth ( 1, width - smallWidth*2 );
    m_Layout->setColumnMaximumWidth ( 1, width - smallWidth*2 );

    m_Layout->setColumnMinimumWidth ( 2, smallWidth );
    m_Layout->setColumnMaximumWidth ( 2, smallWidth );


    
    m_Layout->setRowMinimumHeight ( 0, smallHeight );
    m_Layout->setRowMaximumHeight ( 0, smallHeight );

    m_Layout->setRowMinimumHeight ( 1, height - smallHeight*2 );
    m_Layout->setRowMaximumHeight ( 1, height - smallHeight*2 );

    m_Layout->setRowMinimumHeight ( 2, smallHeight );
    m_Layout->setRowMaximumHeight ( 2, smallHeight );

    m_Layout->setMargin(0);
    m_Layout->setPadding(0);


    /* //only test
    for (int yy =0; yy<3; yy++)
        for (int xx =0; xx<3; xx++)
            m_Layout->addItem(new DuiButton("text"), xx, yy, Qt::AlignCenter);
     */


    QPixmap *tmpPixmap = new QPixmap(image);
    //QPixmap *copyPixmap = new QPixmap(tmpPixmap->copy(0 , 0, 50, 50));
    //m_Image = new DuiImage(copyPixmap);
  
    qDebug() << "image     =============      " << tmpPixmap->size().width() << tmpPixmap->size().height();

    int originalMiddleWidth = tmpPixmap->width() - smallWidth*2;
    int originalMiddleHeight = tmpPixmap->height() - smallHeight*2;

    int newMiddleWidth = width - smallWidth*2;
    int newMiddleHeight = height - smallHeight*2;


    m_ImageLeftUp = initImageFix(tmpPixmap, 0, 0, smallWidth, smallHeight);

    m_ImageLeftMiddle = initImageResize(tmpPixmap, 0, smallHeight,
                                                   smallWidth, originalMiddleHeight,
                                                   smallWidth, newMiddleHeight);

    m_ImageLeftDown = initImageFix(tmpPixmap, 0 , tmpPixmap->height() - smallHeight, smallWidth, smallHeight);


    m_ImageUp = initImageResize(tmpPixmap, smallWidth , 0,
                                           originalMiddleWidth, smallHeight,
                                           newMiddleWidth, smallHeight);
 
    m_ImageMiddle = initImageResize(tmpPixmap, smallWidth, smallHeight,
                                               originalMiddleWidth, originalMiddleHeight, 
                                               newMiddleWidth, newMiddleHeight);

    m_ImageDown = initImageResize(tmpPixmap, smallWidth , tmpPixmap->height() - smallHeight,
                                             originalMiddleWidth, smallHeight, 
                                             newMiddleWidth, smallHeight);


    m_ImageRightUp = initImageFix(tmpPixmap, tmpPixmap->width() - smallWidth, 0, smallWidth, smallHeight);

    m_ImageRightMiddle = initImageResize(tmpPixmap, tmpPixmap->width() - smallWidth, smallHeight,
                                                    smallWidth, originalMiddleHeight,
                                                    smallWidth, newMiddleHeight);

    m_ImageRightDown = initImageFix(tmpPixmap, tmpPixmap->width() - smallWidth, tmpPixmap->height() - smallHeight, smallWidth, smallHeight);
      


    m_Layout->addItem(m_ImageLeftUp, 0, 0, Qt::AlignCenter);
    m_Layout->addItem(m_ImageLeftMiddle, 1, 0, Qt::AlignCenter);
    m_Layout->addItem(m_ImageLeftDown, 2, 0, Qt::AlignCenter);
    
    m_Layout->addItem(m_ImageUp, 0, 1, Qt::AlignCenter);
    m_Layout->addItem(m_ImageMiddle, 1, 1, Qt::AlignCenter);
    m_Layout->addItem(m_ImageDown, 2, 1, Qt::AlignCenter);
    
    m_Layout->addItem(m_ImageRightUp, 0, 2, Qt::AlignCenter);
    m_Layout->addItem(m_ImageRightMiddle, 1, 2, Qt::AlignCenter);
    m_Layout->addItem(m_ImageRightDown, 2, 2, Qt::AlignCenter);



/* ok
    QPixmap *pixmap = new QPixmap(image);
    QPixmap *copyPixmap = new QPixmap(pixmap->copy(0, 0, 55, 55));
    
    DuiImage *_image = new DuiImage(copyPixmap);
    _image->setMinimumWidth(width);
    _image->setMaximumWidth(width);
    _image->setMinimumHeight(height);
    _image->setMaximumHeight(height);

    m_ImageRightDown = new DuiImage(_image);
    m_Layout->addItem(m_ImageRightDown, 2, 2, Qt::AlignCenter);
*/


 //   connect(m_Button, SIGNAL(clicked()), this, SLOT(labelButtonClicked()));

 //   m_Button->setZValue(1);
    
 //   m_Label->setZValue(2);
 //   m_Image->setZValue(3);

 //   m_Image->translate(-TRANSLATEX, -TRANSLATEY);
}

DuiImage* DcpSpec::initImageFix(const QPixmap* pixmap, int x, int y, int width, int height)
{

    QPixmap *copyPixmap = new QPixmap(pixmap->copy(x, y, width, height));

    DuiImage* image = new DuiImage(copyPixmap);
    image->setMinimumWidth(width);
    image->setMaximumWidth(width);
    image->setMinimumHeight(height);
    image->setMaximumHeight(height);

    //m_Image->setAcceptedMouseButtons(0);

  delete copyPixmap;

  return image;
}

DuiImage* DcpSpec::initImageResize(const QPixmap* pixmap, int x, int y, int width, int height, int newWidth, int newHeight)
{

    QPixmap *copyPixmap = new QPixmap(pixmap->copy(x, y, width, height).scaled(newWidth, newHeight));

    DuiImage* image = new DuiImage(copyPixmap);
    image->setMinimumWidth(newWidth);
    image->setMaximumWidth(newWidth);
    image->setMinimumHeight(newHeight);
    image->setMaximumHeight(newHeight);

    //m_Image->setAcceptedMouseButtons(0);

  delete copyPixmap;

  return image;
}



DuiGridLayout* DcpSpec::layout()
{
    return m_Layout;
}

void DcpSpec::labelButtonClicked()
{
    qDebug() << "labelButtonClicked";
    emit clicked("labelButtonClicked");
}

