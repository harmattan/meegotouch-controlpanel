#include "dcpbutton2toggle.h"
#include <DuiLayout>

DcpButton2Toggle::DcpButton2Toggle(DuiWidget* parent)
    : DcpButton2Align(parent, false)
{
    this->setLayout(createLayout());
}

QGraphicsLayout* DcpButton2Toggle::createLayout()
{
    // toggle
    DuiButton* toggleButton = new DuiButton(this);
    toggleButton->setObjectName("DcpButtonToggle");
    toggleButton->setCheckable(true);
    connect (toggleButton, SIGNAL(toggled(bool)),
             this, SLOT(onSmallToggled(bool)));

    setAlignedWidget(toggleButton);

    return DcpButton2Align::createLayout();
}

void DcpButton2Toggle::setText2(const QString& text)
{
    m_Text2 = text;

    // only update if toggle is on
    if (toggleButton()->isChecked()) {
        DcpButton2::setText2(m_Text2);
    }
}

void DcpButton2Toggle::onSmallToggled (bool isOn)
{
    // do not show second line in case it is off:
    if (isOn){
        DcpButton2::setText2(m_Text2);
    } else {
        DcpButton2::setText2(QString());
    }

    // emit signal
    emit smallToggled(isOn);
}

void DcpButton2Toggle::setSmallToggle(bool isOn)
{
    toggleButton()->setChecked(isOn);
}

DuiButton* DcpButton2Toggle::toggleButton()
{
    return qobject_cast<DuiButton*>(alignedWidget());
}

