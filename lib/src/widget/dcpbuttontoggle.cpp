/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpbuttontoggle.h"
#include <DuiLayout>
#include <DuiButton>

DcpButtonToggle::DcpButtonToggle(DuiWidget* parent)
    : DcpButtonAlign(parent, false)
{
    this->setLayout(createLayout());
}

QGraphicsLayout* DcpButtonToggle::createLayout()
{
    // toggle
    DuiButton* toggleButton = new DuiButton(this);
    toggleButton->setObjectName("DcpButtonToggle");
    toggleButton->setCheckable(true);
    connect (toggleButton, SIGNAL(toggled(bool)),
             this, SLOT(onSmallToggled(bool)));

    setAlignedWidget(toggleButton);

    return DcpButtonAlign::createLayout();
}

void DcpButtonToggle::setText2(const QString& text)
{
    m_Text2 = text;

    // only update if toggle is on
    if (toggleButton()->isChecked()) {
        DcpButton::setText2(m_Text2);
    }
}

void DcpButtonToggle::onSmallToggled (bool isOn)
{
    // do not show second line in case it is off:
    if (isOn){
        DcpButton::setText2(m_Text2);
    } else {
        DcpButton::setText2(QString());
    }

    // emit signal
    emit smallToggled(isOn);
}

void DcpButtonToggle::setSmallToggle(bool isOn)
{
    if (toggleButton()->isChecked() != isOn) {
        toggleButton()->setChecked(isOn);
    }
}

DuiButton* DcpButtonToggle::toggleButton()
{
    return qobject_cast<DuiButton*>(alignedWidget());
}

void DcpButtonToggle::setIconId(const QString& iconId)
{
    if (iconId != this->iconId()) {
        toggleButton()->setIconID(iconId);
    }
}

QString DcpButtonToggle::iconId()
{
    return toggleButton()->iconID();
}

