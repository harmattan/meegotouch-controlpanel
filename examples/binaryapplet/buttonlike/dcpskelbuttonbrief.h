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

#ifndef SKELBUTTONBRIEF_H
#define SKELBUTTONBRIEF_H

#include <DcpBrief>

class SkelButtonBrief: public DcpBrief{
    Q_OBJECT
public:
    SkelButtonBrief();
    virtual QString valueText() const;
    virtual QString titleText() const;

    virtual bool toggle() const;
    virtual void setToggle (bool toggle);
    virtual int widgetTypeID() const;

private:
    bool m_ToggleState;
};


#endif // SKELBUTTONBRIEF
