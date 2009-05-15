#ifndef LANGUAGEWIDGET_H
#define LANGUAGEWIDGET_H

#include "dcpwidget.h" 

class DcpButton;
class DcpDialog;

class LanguageWidget : public DcpWidget 
{
	Q_OBJECT
		
public:
	LanguageWidget(QGraphicsWidget *parent = 0);
	virtual ~LanguageWidget();
    virtual bool back();
    
protected:
	void initWidget();
    void updateLanguageButtons();

private:
    DcpButton *m_DisplayButton;
    DcpButton *m_KeyboardButton;
    DcpDialog *m_Dlg;
    
private slots:
    virtual void displayPage();
    virtual void keyboardPage();
};
#endif // LANGUAGEWIDGET_H
