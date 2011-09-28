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

#include "bsuppliercommands.h"

const QString BSupplier::BServerId = "dcpbriefs";

// available commands (m_Input):
const QString BSupplier::CmdWatch = "watch ";
const QString BSupplier::CmdUnwatch = "unwatch ";
const QString BSupplier::CmdSetValue = "setvalue ";

// available responses (output):
const char* BSupplier::OutputBegin = "BEGIN";
const char* BSupplier::OutputEnd = "END";

// data identifiers:
const char* BSupplier::OutputName = "name";
const char* BSupplier::OutputWidgetTypeID = "widgetTypeID";
const char* BSupplier::OutputValueText = "valueText";
const char* BSupplier::OutputIcon = "icon";
const char* BSupplier::OutputTitleText = "titleText";
const char* BSupplier::OutputHelpId = "helpId";
const char* BSupplier::OutputValue = "value";
const char* BSupplier::OutputMinValue = "minValue";
const char* BSupplier::OutputMaxValue = "maxValue";
const char* BSupplier::OutputValueStep = "sliderSteps";
const char* BSupplier::OutputPossibleValues = "possibleValues";

const QChar BSupplier::ParamSeparator;

