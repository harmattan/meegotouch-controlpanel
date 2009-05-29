#ifndef DCPBUTTONSTYLEDATA_H
#define DCPBUTTONSTYLEDATA_H

#include "dcpbuttonstyle.h"

class DcpButtonStyleData
{
    friend class DcpButtonStyle;
public:
    DcpButtonStyleData();
    virtual ~DcpButtonStyleData() {}
private:
    int fieldMarginLeft;
    int fieldMarginRight;
    int fieldMarginTop;
    int fieldMarginBottom;
    int fieldMarginMiddle;
    QString backgroundImage;
    QSize backgroundSize;
    QColor textColor0;
    QColor textColor1;
    QColor textColor2;
    QFont font0;
    QFont font1;
    QFont font2;
    QColor textOffColor;
    QSize textSize1;
    QPointF textPos1;
    QSize textSize2;
    QPointF textPos2;
    Qt::Alignment textAlign0;
    Qt::Alignment textAlign1;
    Qt::Alignment textAlign2;
    QString triangleBackground;
    QSize triangleBackgroundSize;
    QPointF trianglePos;
    int marginTriangle;
    QSize imageSize;
    int marginSpacer;
    QString backgroundBorder;
    QString toggleOn;
    QString toggleOff;
};

class DcpButtonStyleContainerPrivate
{
    friend class DcpButtonStyleContainer;
public:
    DcpButtonStyleContainerPrivate();
    virtual ~DcpButtonStyleContainerPrivate();
private:
};

#endif
