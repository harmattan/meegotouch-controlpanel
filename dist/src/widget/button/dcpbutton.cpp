
#include "dcpbutton.h"
#include "dcpbuttonview.h"

DcpButton::DcpButton(const QString &title, DuiWidget *parent, const QString &type) : DuiButton(title, parent, type)
{

		m_View = new DcpButtonView(*this);

    setView(m_View);

    setObjectName("DcpButton");

		connect(m_View, SIGNAL(clicked()), this, SIGNAL(clicked()));

    setMaximumWidth(m_View->width());
    setMaximumHeight(m_View->height());
}

void DcpButton::setText(const QString& text1, const QString& text2)
{
		m_View->setText1(text1);
		m_View->setText2(text2);
}

DcpButton::~DcpButton()
{
}
