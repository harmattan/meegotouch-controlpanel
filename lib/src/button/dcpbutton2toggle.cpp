#include "dcpbutton2toggle.h"

#include <DuiLayout>
#include <DuiLinearLayoutPolicy>

DcpButton2Toggle::DcpButton2Toggle(DuiWidget* parent)
    : DcpButton2(parent, false)
{
    this->setLayout(createLayout());
}

DuiLayout* DcpButton2Toggle::createLayout()
{
    // text
    DuiLayout* textLayout = DcpButton2::createLayout();
    qreal left, right, top, bottom;
    textLayout->getContentsMargins(&left, &top, &right, &bottom);
    textLayout->setContentsMargins(0,0,right,0);

    // toggle
    m_ToggleButton = new DuiButton(this);
    m_ToggleButton->setObjectName("DcpButtonToggle");
    m_ToggleButton->setCheckable(true);
    connect (m_ToggleButton, SIGNAL(toggled(bool)),
             this, SLOT(onSmallToggled(bool)));

    // putting them together on the layout:
    DuiLayout* layout = new DuiLayout(0);
    layout->setAnimator(0);
    layout->setContentsMargins(left,top,right,bottom);
    DuiLinearLayoutPolicy* vertLayoutPolicy = new DuiLinearLayoutPolicy(layout,
            Qt::Horizontal);
    vertLayoutPolicy->addItemAtPosition(textLayout, 0);
    vertLayoutPolicy->addItemAtPosition(m_ToggleButton, 1);

    return layout;
}

void DcpButton2Toggle::setText2(const QString& text)
{
    m_Text2 = text;

    // only update if toggle is on
    if (m_ToggleButton->isChecked()) {
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
    m_ToggleButton->setChecked(true);
}

