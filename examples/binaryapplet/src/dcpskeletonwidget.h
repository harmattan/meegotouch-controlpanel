/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#ifndef SKELETONWIDGET_H
#define SKELETONWIDGET_H

#include <DcpWidget>
 
class MLabel;

class SkeletonWidget : public DcpWidget 
{
	Q_OBJECT
		
public:
	SkeletonWidget(QGraphicsWidget *parent = 0);
	virtual ~SkeletonWidget();

protected:
	void initWidget();
		
private:
	MLabel    *m_aboutLabel;
		
};
#endif // SKELETONWIDGET_H
