
#ifndef DCPBUTTON_H
#define DCPBUTTON_H

#include <DuiButton>
#include <QString>

#include "dcpwidgettypes.h"

class DcpButton : public DuiButton
{
    Q_OBJECT

public:
    DcpButton(int buttonType, const QString &title = "", DuiWidget *parent = NULL, const QString &type = "");
    virtual ~DcpButton();

	void setText(const QString& text1, const QString& text2);

	void setAlignment(Qt::Alignment alignment);

signals:
    void clicked();

protected:
	class DcpButtonView *m_View;

};

#endif // DCPBUTTON_H
