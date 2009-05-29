#include "dcpbuttonstyle.h"
#include "gen_dcpbuttonstyledata.h"
#include "duistylecreator.h"
#include "duitheme.h"

DUI_REGISTER_STYLE(DcpButtonStyle)

DcpButtonStyleData::DcpButtonStyleData()
{
}

DcpButtonStyle::DcpButtonStyle() :
    DuiWidgetStyle(),
    data(new DcpButtonStyleData)
{
}

DcpButtonStyle::~DcpButtonStyle()
{
    delete data;
}

DcpButtonStyle::DcpButtonStyle(DcpButtonStyleData* data) :
    DuiWidgetStyle(),
    data(data)
{
}

const int& DcpButtonStyle::fieldMarginLeft() const
{
    return static_cast<const DcpButtonStyleData*>(data)->fieldMarginLeft;
}

void DcpButtonStyle::setFieldMarginLeft(const int& fieldMarginLeft)
{
    if(static_cast<DcpButtonStyleData*>(data)->fieldMarginLeft != fieldMarginLeft) {
        static_cast<DcpButtonStyleData*>(data)->fieldMarginLeft = fieldMarginLeft;
    }
}

const int& DcpButtonStyle::fieldMarginRight() const
{
    return static_cast<const DcpButtonStyleData*>(data)->fieldMarginRight;
}

void DcpButtonStyle::setFieldMarginRight(const int& fieldMarginRight)
{
    if(static_cast<DcpButtonStyleData*>(data)->fieldMarginRight != fieldMarginRight) {
        static_cast<DcpButtonStyleData*>(data)->fieldMarginRight = fieldMarginRight;
    }
}

const int& DcpButtonStyle::fieldMarginTop() const
{
    return static_cast<const DcpButtonStyleData*>(data)->fieldMarginTop;
}

void DcpButtonStyle::setFieldMarginTop(const int& fieldMarginTop)
{
    if(static_cast<DcpButtonStyleData*>(data)->fieldMarginTop != fieldMarginTop) {
        static_cast<DcpButtonStyleData*>(data)->fieldMarginTop = fieldMarginTop;
    }
}

const int& DcpButtonStyle::fieldMarginBottom() const
{
    return static_cast<const DcpButtonStyleData*>(data)->fieldMarginBottom;
}

void DcpButtonStyle::setFieldMarginBottom(const int& fieldMarginBottom)
{
    if(static_cast<DcpButtonStyleData*>(data)->fieldMarginBottom != fieldMarginBottom) {
        static_cast<DcpButtonStyleData*>(data)->fieldMarginBottom = fieldMarginBottom;
    }
}

const int& DcpButtonStyle::fieldMarginMiddle() const
{
    return static_cast<const DcpButtonStyleData*>(data)->fieldMarginMiddle;
}

void DcpButtonStyle::setFieldMarginMiddle(const int& fieldMarginMiddle)
{
    if(static_cast<DcpButtonStyleData*>(data)->fieldMarginMiddle != fieldMarginMiddle) {
        static_cast<DcpButtonStyleData*>(data)->fieldMarginMiddle = fieldMarginMiddle;
    }
}

const QString& DcpButtonStyle::backgroundImage() const
{
    return static_cast<const DcpButtonStyleData*>(data)->backgroundImage;
}

void DcpButtonStyle::setBackgroundImage(const QString& backgroundImage)
{
    if(static_cast<DcpButtonStyleData*>(data)->backgroundImage != backgroundImage) {
        static_cast<DcpButtonStyleData*>(data)->backgroundImage = backgroundImage;
    }
}

const QSize& DcpButtonStyle::backgroundSize() const
{
    return static_cast<const DcpButtonStyleData*>(data)->backgroundSize;
}

void DcpButtonStyle::setBackgroundSize(const QSize& backgroundSize)
{
    if(static_cast<DcpButtonStyleData*>(data)->backgroundSize != backgroundSize) {
        static_cast<DcpButtonStyleData*>(data)->backgroundSize = backgroundSize;
    }
}

const QColor& DcpButtonStyle::textColor0() const
{
    return static_cast<const DcpButtonStyleData*>(data)->textColor0;
}

void DcpButtonStyle::setTextColor0(const QColor& textColor0)
{
    if(static_cast<DcpButtonStyleData*>(data)->textColor0 != textColor0) {
        static_cast<DcpButtonStyleData*>(data)->textColor0 = textColor0;
    }
}

const QColor& DcpButtonStyle::textColor1() const
{
    return static_cast<const DcpButtonStyleData*>(data)->textColor1;
}

void DcpButtonStyle::setTextColor1(const QColor& textColor1)
{
    if(static_cast<DcpButtonStyleData*>(data)->textColor1 != textColor1) {
        static_cast<DcpButtonStyleData*>(data)->textColor1 = textColor1;
    }
}

const QColor& DcpButtonStyle::textColor2() const
{
    return static_cast<const DcpButtonStyleData*>(data)->textColor2;
}

void DcpButtonStyle::setTextColor2(const QColor& textColor2)
{
    if(static_cast<DcpButtonStyleData*>(data)->textColor2 != textColor2) {
        static_cast<DcpButtonStyleData*>(data)->textColor2 = textColor2;
    }
}

const QFont& DcpButtonStyle::font0() const
{
    return static_cast<const DcpButtonStyleData*>(data)->font0;
}

void DcpButtonStyle::setFont0(const QFont& font0)
{
    if(static_cast<DcpButtonStyleData*>(data)->font0 != font0) {
        static_cast<DcpButtonStyleData*>(data)->font0 = font0;
    }
}

const QFont& DcpButtonStyle::font1() const
{
    return static_cast<const DcpButtonStyleData*>(data)->font1;
}

void DcpButtonStyle::setFont1(const QFont& font1)
{
    if(static_cast<DcpButtonStyleData*>(data)->font1 != font1) {
        static_cast<DcpButtonStyleData*>(data)->font1 = font1;
    }
}

const QFont& DcpButtonStyle::font2() const
{
    return static_cast<const DcpButtonStyleData*>(data)->font2;
}

void DcpButtonStyle::setFont2(const QFont& font2)
{
    if(static_cast<DcpButtonStyleData*>(data)->font2 != font2) {
        static_cast<DcpButtonStyleData*>(data)->font2 = font2;
    }
}

const QColor& DcpButtonStyle::textOffColor() const
{
    return static_cast<const DcpButtonStyleData*>(data)->textOffColor;
}

void DcpButtonStyle::setTextOffColor(const QColor& textOffColor)
{
    if(static_cast<DcpButtonStyleData*>(data)->textOffColor != textOffColor) {
        static_cast<DcpButtonStyleData*>(data)->textOffColor = textOffColor;
    }
}

const QSize& DcpButtonStyle::textSize1() const
{
    return static_cast<const DcpButtonStyleData*>(data)->textSize1;
}

void DcpButtonStyle::setTextSize1(const QSize& textSize1)
{
    if(static_cast<DcpButtonStyleData*>(data)->textSize1 != textSize1) {
        static_cast<DcpButtonStyleData*>(data)->textSize1 = textSize1;
    }
}

const QPointF& DcpButtonStyle::textPos1() const
{
    return static_cast<const DcpButtonStyleData*>(data)->textPos1;
}

void DcpButtonStyle::setTextPos1(const QPointF& textPos1)
{
    if(static_cast<DcpButtonStyleData*>(data)->textPos1 != textPos1) {
        static_cast<DcpButtonStyleData*>(data)->textPos1 = textPos1;
    }
}

const QSize& DcpButtonStyle::textSize2() const
{
    return static_cast<const DcpButtonStyleData*>(data)->textSize2;
}

void DcpButtonStyle::setTextSize2(const QSize& textSize2)
{
    if(static_cast<DcpButtonStyleData*>(data)->textSize2 != textSize2) {
        static_cast<DcpButtonStyleData*>(data)->textSize2 = textSize2;
    }
}

const QPointF& DcpButtonStyle::textPos2() const
{
    return static_cast<const DcpButtonStyleData*>(data)->textPos2;
}

void DcpButtonStyle::setTextPos2(const QPointF& textPos2)
{
    if(static_cast<DcpButtonStyleData*>(data)->textPos2 != textPos2) {
        static_cast<DcpButtonStyleData*>(data)->textPos2 = textPos2;
    }
}

const Qt::Alignment& DcpButtonStyle::textAlign0() const
{
    return static_cast<const DcpButtonStyleData*>(data)->textAlign0;
}

void DcpButtonStyle::setTextAlign0(const Qt::Alignment& textAlign0)
{
    if(static_cast<DcpButtonStyleData*>(data)->textAlign0 != textAlign0) {
        static_cast<DcpButtonStyleData*>(data)->textAlign0 = textAlign0;
    }
}

const Qt::Alignment& DcpButtonStyle::textAlign1() const
{
    return static_cast<const DcpButtonStyleData*>(data)->textAlign1;
}

void DcpButtonStyle::setTextAlign1(const Qt::Alignment& textAlign1)
{
    if(static_cast<DcpButtonStyleData*>(data)->textAlign1 != textAlign1) {
        static_cast<DcpButtonStyleData*>(data)->textAlign1 = textAlign1;
    }
}

const Qt::Alignment& DcpButtonStyle::textAlign2() const
{
    return static_cast<const DcpButtonStyleData*>(data)->textAlign2;
}

void DcpButtonStyle::setTextAlign2(const Qt::Alignment& textAlign2)
{
    if(static_cast<DcpButtonStyleData*>(data)->textAlign2 != textAlign2) {
        static_cast<DcpButtonStyleData*>(data)->textAlign2 = textAlign2;
    }
}

const QString& DcpButtonStyle::triangleBackground() const
{
    return static_cast<const DcpButtonStyleData*>(data)->triangleBackground;
}

void DcpButtonStyle::setTriangleBackground(const QString& triangleBackground)
{
    if(static_cast<DcpButtonStyleData*>(data)->triangleBackground != triangleBackground) {
        static_cast<DcpButtonStyleData*>(data)->triangleBackground = triangleBackground;
    }
}

const QSize& DcpButtonStyle::triangleBackgroundSize() const
{
    return static_cast<const DcpButtonStyleData*>(data)->triangleBackgroundSize;
}

void DcpButtonStyle::setTriangleBackgroundSize(const QSize& triangleBackgroundSize)
{
    if(static_cast<DcpButtonStyleData*>(data)->triangleBackgroundSize != triangleBackgroundSize) {
        static_cast<DcpButtonStyleData*>(data)->triangleBackgroundSize = triangleBackgroundSize;
    }
}

const QPointF& DcpButtonStyle::trianglePos() const
{
    return static_cast<const DcpButtonStyleData*>(data)->trianglePos;
}

void DcpButtonStyle::setTrianglePos(const QPointF& trianglePos)
{
    if(static_cast<DcpButtonStyleData*>(data)->trianglePos != trianglePos) {
        static_cast<DcpButtonStyleData*>(data)->trianglePos = trianglePos;
    }
}

const int& DcpButtonStyle::marginTriangle() const
{
    return static_cast<const DcpButtonStyleData*>(data)->marginTriangle;
}

void DcpButtonStyle::setMarginTriangle(const int& marginTriangle)
{
    if(static_cast<DcpButtonStyleData*>(data)->marginTriangle != marginTriangle) {
        static_cast<DcpButtonStyleData*>(data)->marginTriangle = marginTriangle;
    }
}

const QSize& DcpButtonStyle::imageSize() const
{
    return static_cast<const DcpButtonStyleData*>(data)->imageSize;
}

void DcpButtonStyle::setImageSize(const QSize& imageSize)
{
    if(static_cast<DcpButtonStyleData*>(data)->imageSize != imageSize) {
        static_cast<DcpButtonStyleData*>(data)->imageSize = imageSize;
    }
}

const int& DcpButtonStyle::marginSpacer() const
{
    return static_cast<const DcpButtonStyleData*>(data)->marginSpacer;
}

void DcpButtonStyle::setMarginSpacer(const int& marginSpacer)
{
    if(static_cast<DcpButtonStyleData*>(data)->marginSpacer != marginSpacer) {
        static_cast<DcpButtonStyleData*>(data)->marginSpacer = marginSpacer;
    }
}

const QString& DcpButtonStyle::backgroundBorder() const
{
    return static_cast<const DcpButtonStyleData*>(data)->backgroundBorder;
}

void DcpButtonStyle::setBackgroundBorder(const QString& backgroundBorder)
{
    if(static_cast<DcpButtonStyleData*>(data)->backgroundBorder != backgroundBorder) {
        static_cast<DcpButtonStyleData*>(data)->backgroundBorder = backgroundBorder;
    }
}

const QString& DcpButtonStyle::toggleOn() const
{
    return static_cast<const DcpButtonStyleData*>(data)->toggleOn;
}

void DcpButtonStyle::setToggleOn(const QString& toggleOn)
{
    if(static_cast<DcpButtonStyleData*>(data)->toggleOn != toggleOn) {
        static_cast<DcpButtonStyleData*>(data)->toggleOn = toggleOn;
    }
}

const QString& DcpButtonStyle::toggleOff() const
{
    return static_cast<const DcpButtonStyleData*>(data)->toggleOff;
}

void DcpButtonStyle::setToggleOff(const QString& toggleOff)
{
    if(static_cast<DcpButtonStyleData*>(data)->toggleOff != toggleOff) {
        static_cast<DcpButtonStyleData*>(data)->toggleOff = toggleOff;
    }
}

///////////////
// CONTAINER //
///////////////

DcpButtonStyleContainerPrivate::DcpButtonStyleContainerPrivate()
{
}

DcpButtonStyleContainerPrivate::~DcpButtonStyleContainerPrivate()
{
}


DcpButtonStyleContainer::DcpButtonStyleContainer() :
    DuiWidgetStyleContainer(),
    d_ptr(new DcpButtonStyleContainerPrivate)
{
}

DcpButtonStyleContainer::DcpButtonStyleContainer(DcpButtonStyleContainerPrivate* dd) :
    DuiWidgetStyleContainer(),
    d_ptr(dd)
{
}

DcpButtonStyleContainer::~DcpButtonStyleContainer()
{
    delete d_ptr;
}

const DcpButtonStyle* DcpButtonStyleContainer::operator->() const
{
    return static_cast<const DcpButtonStyle*>(currentStyle());
}

void DcpButtonStyleContainer::reloadStyles()
{
    DuiWidgetStyleContainer::reloadStyles();
}

const char* DcpButtonStyleContainer::styleType() const
{
    return "DcpButtonStyle";
}

