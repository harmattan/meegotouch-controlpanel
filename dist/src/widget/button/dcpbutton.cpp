
#include "dcpbutton.h"

#include "dcpbuttonview.h"
#include "dcpbutton2view.h"

#include "dcpbutton2imageview.h"

#include "dcpbutton2imageview.h"
#include "dcpbutton2toggleview.h"

DcpButton::DcpButton(int buttonType, const QString &title, DuiWidget *parent, const QString &type) : DuiButton(title, parent)
{

	switch (buttonType) {
		case DCPLABEL :
		break;
		case DCPLABEL2 :
			m_View = new DcpButton2View(*this);
		break;
		case DCPLABEL2IMAGE :
			m_View = new DcpButton2ImageView(*this);
		break;
		case DCPLABEL2TOGGLE :
			m_View = new DcpButton2ToggleView(*this);
		break;
	}

    setObjectName("DcpButton");
    setView(m_View);
    m_View->updateStyle();

	connect(m_View, SIGNAL(clicked()), this, SIGNAL(clicked()));

	setMinimumWidth(m_View->width());
//    setMaximumWidth(m_View->width());

	setMinimumHeight(m_View->height());
 //   setMaximumHeight(m_View->height());

}

void DcpButton::setText(const QString& text1, const QString& text2)
{
	m_View->setText1(text1);
	m_View->setText2(text2);
}

DcpButton::~DcpButton()
{
}

void DcpButton::setAlignment(Qt::Alignment alignment)
{
	m_View->setAlignment(alignment);
}

void DcpButton::setLine(bool line)
{
	m_View->setLine(line);
}
