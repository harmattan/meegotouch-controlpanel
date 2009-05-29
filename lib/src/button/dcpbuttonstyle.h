
#ifndef DPCBUTTONSTYLE_H
#define DPCBUTTONSTYLE_H

#include <QSize>
#include <QFont>
#include <QColor>
#include <QPointF>

#include <duiwidgetstyle.h>

class DcpButtonStyle : public DuiWidgetStyle
{
    Q_OBJECT
    DUI_STYLE(DcpButtonStyle)

	DUI_STYLE_ATTRIBUTE(int,            fieldMarginLeft,        	FieldMarginLeft)
	DUI_STYLE_ATTRIBUTE(int,            fieldMarginRight,       	FieldMarginRight)
	DUI_STYLE_ATTRIBUTE(int,            fieldMarginTop,         	FieldMarginTop)
	DUI_STYLE_ATTRIBUTE(int,            fieldMarginBottom,      	FieldMarginBottom)
	DUI_STYLE_ATTRIBUTE(int,            fieldMarginMiddle,      	FieldMarginMiddle)

	DUI_STYLE_ATTRIBUTE(QString,		backgroundImage,			BackgroundImage)

	DUI_STYLE_ATTRIBUTE(QSize,			backgroundSize,      		BackgroundSize)

	DUI_STYLE_ATTRIBUTE(QColor,         textColor0,      			TextColor0)
	DUI_STYLE_ATTRIBUTE(QColor,         textColor1,      			TextColor1)
	DUI_STYLE_ATTRIBUTE(QColor,         textColor2,      			TextColor2)
	

	DUI_STYLE_ATTRIBUTE(QFont,          font0,      				Font0)
	DUI_STYLE_ATTRIBUTE(QFont,          font1,      				Font1)
	DUI_STYLE_ATTRIBUTE(QFont,          font2,      				Font2)

	DUI_STYLE_ATTRIBUTE(QColor,         textOffColor,      			TextOffColor)

	DUI_STYLE_ATTRIBUTE(QSize,          textSize1,      			TextSize1)
	DUI_STYLE_ATTRIBUTE(QPointF,        textPos1,      				TextPos1)

	DUI_STYLE_ATTRIBUTE(QSize,          textSize2,      			TextSize2)
	DUI_STYLE_ATTRIBUTE(QPointF,		textPos2,      				TextPos2)

	DUI_STYLE_ATTRIBUTE(Qt::Alignment,	textAlign0,      			TextAlign0)
	DUI_STYLE_ATTRIBUTE(Qt::Alignment,	textAlign1,      			TextAlign1)
	DUI_STYLE_ATTRIBUTE(Qt::Alignment,	textAlign2,      			TextAlign2)

  	DUI_STYLE_ATTRIBUTE(QString,		triangleBackground,			TriangleBackground)
    DUI_STYLE_ATTRIBUTE(QSize,          triangleBackgroundSize,		TriangleBackgroundSize)
	DUI_STYLE_ATTRIBUTE(QPointF,        trianglePos,      			TrianglePos)

	DUI_STYLE_ATTRIBUTE(int,            marginTriangle,      		MarginTriangle)

//    imageName: image(starfield);
    DUI_STYLE_ATTRIBUTE(QSize,          imageSize,      			ImageSize)

	DUI_STYLE_ATTRIBUTE(int,            marginSpacer,      			MarginSpacer)

  	DUI_STYLE_ATTRIBUTE(QString,		backgroundBorder,			BackgroundBorder)

	DUI_STYLE_ATTRIBUTE(QString,		toggleOn,					ToggleOn)
	DUI_STYLE_ATTRIBUTE(QString,		toggleOff,					ToggleOff)

};

class DcpButtonStyleContainer : public DuiWidgetStyleContainer
{
	DUI_STYLE_CONTAINER(DcpButtonStyle)

};

#endif
