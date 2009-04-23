
#include "dcpbutton.h"

#include "dcpbuttonview.h"
#include "dcpbutton2view.h"

#include "dcpbutton2imageview.h"

DcpButton::DcpButton(const QString &title, DuiWidget *parent, const QString &type) : DuiButton(title, parent, type)
{

		m_View = new DcpButton2ImageView(*this);

    setView(m_View);

    setObjectName("DcpButton");

		connect(m_View, SIGNAL(clicked()), this, SIGNAL(clicked()));

		setMinimumWidth(m_View->width());
    setMaximumWidth(m_View->width());

		setMinimumHeight(m_View->height());
    setMaximumHeight(m_View->height());

		qDebug() << m_View->width() << "     " << m_View->height();

}

void DcpButton::setText(const QString& text1, const QString& text2)
{
		m_View->setText1(text1);
		m_View->setText2(text2);
}

DcpButton::~DcpButton()
{
}
