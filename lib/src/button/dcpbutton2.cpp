#include "dcpbutton2.h"
#include <DuiLabel>
#include <DuiLayout>
#include <DuiLinearLayoutPolicy>

DcpButton2::DcpButton2(DuiWidget* parent)
    : DuiButton(parent), m_Label1(0), m_Label2(0)
{
    DuiLayout* layout = new DuiLayout(this);
    m_LayoutPolicy = new DuiLinearLayoutPolicy(layout, Qt::Vertical);
    this->setLayout(layout);
}

void DcpButton2::setText1(const QString& text)
{
    _setLabelText(m_Label1, 0, text);
}

void DcpButton2::setText2(const QString& text)
{
    _setLabelText(m_Label2, 1, text);
}

inline void DcpButton2::_setLabelText(DuiLabel*& label, int position,
                                      const QString& text)
{
    if (text.isEmpty()){
        if (label){
            delete label;
            label = NULL;
        }
        return;
    }

    if (!label) {
        label = new DuiLabel (this);
        m_LayoutPolicy->addItemAtPosition(label, position);
    }
    label->setText(text);
}


