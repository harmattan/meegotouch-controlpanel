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

#ifndef BSUPPLIERCOMMANDS
#define BSUPPLIERCOMMANDS

#include <QString>
#include <QChar>

namespace BSupplier
{

// server id:
extern const QString BServerId;

// available commands (m_Input):
extern const QString CmdWatch;
extern const QString CmdUnwatch;
extern const QString CmdSetValue;

// available responses (output):
extern const char* OutputBegin;
extern const char* OutputEnd;

// data identifiers:
extern const char* OutputName;
extern const char* OutputWidgetTypeID;
extern const char* OutputValueText;
extern const char* OutputIcon;
extern const char* OutputTitleText;
extern const char* OutputHelpId;
extern const char* OutputValue;
extern const char* OutputMinValue;
extern const char* OutputMaxValue;
extern const char* OutputValueStep;
extern const char* OutputPossibleValues;

// parameter separator:
extern const QChar ParamSeparator;

}

#endif // BSUPPLIERCOMMANDS

