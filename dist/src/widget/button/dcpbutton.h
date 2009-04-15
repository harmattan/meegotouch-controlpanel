
#ifndef DCPBUTTON_H
#define DCPBUTTON_H

#include <DuiButton>
#include <QString>

class DcpButton : public DuiButton
{
    Q_OBJECT

public:
    DcpButton(const QString &title = "", DuiWidget *parent = NULL, const QString &type = "");
    virtual ~DcpButton();

		void setText(const QString& text1, const QString& text2);

signals:
    void clicked();

protected:
		class DcpButtonView *m_View;

};

#endif // DCPBUTTON_H
