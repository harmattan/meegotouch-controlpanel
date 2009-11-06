#include "dcpbuttontoggle.h"
#include <DuiLayout>

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
    toggleButton()->setChecked(isOn);
}

DuiButton* DcpButtonToggle::toggleButton()
{
    return qobject_cast<DuiButton*>(alignedWidget());
}

